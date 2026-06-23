// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/connection/ServerNetworkSystem.hpp"
#include "sculk/protocol/codec/MinecraftPackets.hpp"
#include "sculk/protocol/connection/detail/RakPacketOwner.hpp"
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <algorithm>
#include <array>
#include <chrono>
#include <cstring>
#include <format>
#include <thread>

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

namespace {

constexpr std::uint8_t MINECRAFT_BATCH_PACKET_ID = 0xFE;
constexpr auto         RECEIVE_TICK_INTERVAL     = std::chrono::milliseconds(1);
constexpr auto         FLUSH_TICK_INTERVAL       = std::chrono::milliseconds(1);
constexpr std::size_t  FLUSH_WINDOW_TICKS        = 20;

[[nodiscard]] std::size_t flushBudgetPerTick(std::size_t sessionsCount) noexcept {
    if (sessionsCount == 0) {
        return 0;
    }

    return std::max<std::size_t>(1, (sessionsCount + (FLUSH_WINDOW_TICKS - 1)) / FLUSH_WINDOW_TICKS);
}

} // namespace

ServerNetworkSystem::ServerNetworkSystem(std::size_t workerThreadCount)
: mMotd("Sculk Protocol Library"),
  mPeer(RakNet::RakPeerInterface::GetInstance()),
  mOwnedThreadPool(std::make_unique<thread::ThreadPool>(workerThreadCount)),
  mThreadPool(mOwnedThreadPool.get()) {}

ServerNetworkSystem::ServerNetworkSystem(thread::ThreadPool& threadPool)
: mMotd("Sculk Protocol Library"),
  mPeer(RakNet::RakPeerInterface::GetInstance()),
  mOwnedThreadPool(nullptr),
  mThreadPool(&threadPool) {}

ServerNetworkSystem::~ServerNetworkSystem() { stop(); }

NetworkStartResult
ServerNetworkSystem::start(std::uint16_t ipv4Port, std::uint16_t ipv6Port, std::uint32_t maxConnections) {
    if (mRunning.exchange(true, std::memory_order_acq_rel)) {
        return NetworkStartResult::AlreadyStarted;
    }

    mIpv4Port       = ipv4Port;
    mIpv6Port       = ipv6Port;
    mMaxConnections = maxConnections;

    std::array<RakNet::SocketDescriptor, 2> descriptors{
        RakNet::SocketDescriptor{mIpv4Port,  nullptr},
        RakNet::SocketDescriptor{*mIpv6Port, nullptr}
    };
    descriptors[0].socketFamily = AF_INET;
    descriptors[1].socketFamily = AF_INET6;

    auto status = mPeer->Startup(mMaxConnections, descriptors.data(), 2);
    if (status != RakNet::StartupResult::RAKNET_STARTED) {
        mRunning.store(false, std::memory_order_release);
        return static_cast<NetworkStartResult>(status);
    }

    mPeer->SetMaximumIncomingConnections(mMaxConnections);
    updateAnnouncement();

    mReceiveThread = std::jthread([this](std::stop_token token) { receiveLoop(token); });
    mFlushThread   = std::jthread([this](std::stop_token token) { flushLoop(token); });
    return NetworkStartResult::Success;
}

NetworkStartResult ServerNetworkSystem::start(
    const std::string& ipv4Host,
    std::uint16_t      ipv4Port,
    const std::string& ipv6Host,
    std::uint16_t      ipv6Port,
    std::uint32_t      maxConnections
) {
    if (mRunning.exchange(true, std::memory_order_acq_rel)) {
        return NetworkStartResult::AlreadyStarted;
    }

    mIpv4Port       = ipv4Port;
    mIpv6Port       = ipv6Port;
    mMaxConnections = maxConnections;

    std::array<RakNet::SocketDescriptor, 2> descriptors{
        RakNet::SocketDescriptor{mIpv4Port,  ipv4Host.c_str()},
        RakNet::SocketDescriptor{*mIpv6Port, ipv6Host.c_str()}
    };
    descriptors[0].socketFamily = AF_INET;
    descriptors[1].socketFamily = AF_INET6;

    auto status = mPeer->Startup(mMaxConnections, descriptors.data(), 2);
    if (status != RakNet::StartupResult::RAKNET_STARTED) {
        mRunning.store(false, std::memory_order_release);
        return static_cast<NetworkStartResult>(status);
    }

    mPeer->SetMaximumIncomingConnections(mMaxConnections);
    updateAnnouncement();

    mReceiveThread = std::jthread([this](std::stop_token token) { receiveLoop(token); });
    mFlushThread   = std::jthread([this](std::stop_token token) { flushLoop(token); });
    return NetworkStartResult::Success;
}

NetworkStartResult ServerNetworkSystem::start(std::uint16_t ipv4Port, std::uint32_t maxConnections) {
    if (mRunning.exchange(true, std::memory_order_acq_rel)) {
        return NetworkStartResult::AlreadyStarted;
    }

    mIpv4Port       = ipv4Port;
    mIpv6Port       = std::nullopt;
    mMaxConnections = maxConnections;

    RakNet::SocketDescriptor descriptor{mIpv4Port, nullptr};
    descriptor.socketFamily = AF_INET;

    auto status = mPeer->Startup(mMaxConnections, &descriptor, 1);
    if (status != RakNet::StartupResult::RAKNET_STARTED) {
        mRunning.store(false, std::memory_order_release);
        return static_cast<NetworkStartResult>(status);
    }

    mPeer->SetMaximumIncomingConnections(mMaxConnections);
    updateAnnouncement();

    mReceiveThread = std::jthread([this](std::stop_token token) { receiveLoop(token); });
    mFlushThread   = std::jthread([this](std::stop_token token) { flushLoop(token); });
    return NetworkStartResult::Success;
}

NetworkStartResult
ServerNetworkSystem::start(const std::string& ipv4Host, std::uint16_t ipv4Port, std::uint32_t maxConnections) {
    if (mRunning.exchange(true, std::memory_order_acq_rel)) {
        return NetworkStartResult::AlreadyStarted;
    }

    mIpv4Port       = ipv4Port;
    mIpv6Port       = std::nullopt;
    mMaxConnections = maxConnections;

    RakNet::SocketDescriptor descriptor{mIpv4Port, ipv4Host.c_str()};
    descriptor.socketFamily = AF_INET;

    auto status = mPeer->Startup(mMaxConnections, &descriptor, 1);
    if (status != RakNet::StartupResult::RAKNET_STARTED) {
        mRunning.store(false, std::memory_order_release);
        return static_cast<NetworkStartResult>(status);
    }

    mPeer->SetMaximumIncomingConnections(mMaxConnections);
    updateAnnouncement();

    mReceiveThread = std::jthread([this](std::stop_token token) { receiveLoop(token); });
    mFlushThread   = std::jthread([this](std::stop_token token) { flushLoop(token); });
    return NetworkStartResult::Success;
}

void ServerNetworkSystem::setMotd(std::string_view motd) {
    mMotd = motd;
    updateAnnouncement();
}

void ServerNetworkSystem::updateAnnouncement() noexcept {
    auto message = std::format(
        "MCPE;{0};{1};{2};{3};{4};{5};Sculk Sensor Proxy Server;Survival;1;{6};{7};0;",
        mMotd,
        getProtocolVersion(),
        getMinecraftVersion(),
        getSessionsCount(),
        mMaxConnections,
        mPeer->GetMyGUID().ToString(),
        mIpv4Port,
        mIpv6Port.value_or(0)
    );
    std::uint16_t length = static_cast<std::uint16_t>(message.size());
    message.insert(0, 2, '\0');
    message[0] = static_cast<char>((length >> 8) & 0xFF);
    message[1] = static_cast<char>(length & 0xFF);

    mPeer->SetOfflinePingResponse(message.data(), static_cast<unsigned int>(message.size()));
}

void ServerNetworkSystem::setMaxConnections(std::uint32_t maxConnections) {
    mMaxConnections = maxConnections;
    mPeer->SetMaximumIncomingConnections(mMaxConnections);
    updateAnnouncement();
}

void ServerNetworkSystem::stop() {
    if (!mRunning.exchange(false, std::memory_order_acq_rel)) {
        return;
    }

    if (mReceiveThread.joinable()) {
        mReceiveThread.request_stop();
        mReceiveThread.join();
    }

    if (mFlushThread.joinable()) {
        mFlushThread.request_stop();
        mFlushThread.join();
    }

    std::vector<std::shared_ptr<SessionContext>> contexts;
    contexts.reserve(mSessionContexts.size());
    mSessionContexts.for_each([&contexts](const SessionContextsMap::value_type& entry) {
        contexts.push_back(entry.second);
    });

    for (const auto& context : contexts) {
        if (context && context->mSession) {
            context->mSession->disconnect();
        }
    }

    std::vector<RakNet::RakNetGUID> contextKeys;
    contextKeys.reserve(mSessionContexts.size());
    mSessionContexts.for_each([&contextKeys](const SessionContextsMap::value_type& entry) {
        contextKeys.push_back(entry.first);
    });

    for (const auto& key : contextKeys) {
        (void)removeSessionContext(key);
    }

    if (mPeer) {
        mPeer->Shutdown(20);
    }
}

bool ServerNetworkSystem::isRunning() const noexcept { return mRunning.load(std::memory_order_acquire); }

Result<NetworkStatus> ServerNetworkSystem::getClientNetworkStatus(const RakNet::RakNetGUID& guid) const noexcept {
    auto session = getSessionShared(guid);
    if (!session) {
        return error_utils::makeError("Session not found");
    }

    return session->getNetworkStatus();
}

std::size_t ServerNetworkSystem::getSessionsCount() const { return mSessionContexts.size(); }

std::uint64_t ServerNetworkSystem::getDroppedEventCallbackCount() const noexcept {
    std::uint64_t dropped = 0;
    mSessionContexts.for_each([&dropped](const SessionContextsMap::value_type& entry) {
        if (entry.second && entry.second->mStrand) {
            dropped += entry.second->mStrand->droppedCount();
        }
    });
    return dropped;
}

std::shared_ptr<ServerNetworkSystem::SessionContext>
ServerNetworkSystem::getSessionContext(const RakNet::RakNetGUID& guid) const noexcept {
    std::shared_ptr<SessionContext> context{};
    (void)mSessionContexts.if_contains(guid, [&context](const SessionContextsMap::value_type& entry) {
        context = entry.second;
    });
    return context;
}

std::shared_ptr<Session> ServerNetworkSystem::getSessionShared(const RakNet::RakNetGUID& guid) const noexcept {
    auto context = getSessionContext(guid);
    if (!context) {
        return nullptr;
    }

    return context->mSession;
}

Result<> ServerNetworkSystem::setOnConnected(ConnectionEventCallback&& callback) noexcept {
    if (mRunning.load(std::memory_order_acquire)) {
        return error_utils::makeError("Cannot set on connected callback while running");
    }
    mOnConnected = std::move(callback);
    return {};
}

Result<> ServerNetworkSystem::setOnDisconnected(ConnectionEventCallback&& callback) noexcept {
    if (mRunning.load(std::memory_order_acquire)) {
        return error_utils::makeError("Cannot set on disconnected callback while running");
    }
    mOnDisconnected = std::move(callback);
    return {};
}

Result<> ServerNetworkSystem::setOnPacketReceive(PacketReceiveCallback&& callback) noexcept {
    if (mRunning.load(std::memory_order_acquire)) {
        return error_utils::makeError("Cannot set on packet receive callback while running");
    }
    mOnPacketReceive = std::move(callback);
    return {};
}

Result<> ServerNetworkSystem::setOnPacketParseFailed(PacketParseFailedCallback&& callback) noexcept {
    if (mRunning.load(std::memory_order_acquire)) {
        return error_utils::makeError("Cannot set on packet parse failed callback while running");
    }
    if (!mOnPacketReceive) {
        return error_utils::makeError(
            "Cannot set on packet parse failed callback without setting on packet receive callback"
        );
    }
    mOnPacketParseFailed = std::move(callback);
    return {};
}

std::weak_ptr<Session> ServerNetworkSystem::getSession(const RakNet::RakNetGUID& guid) const noexcept {
    return getSessionShared(guid);
}

void ServerNetworkSystem::disconnectClient(const RakNet::RakNetGUID& guid) noexcept {
    auto context = removeSessionContext(guid);
    if (!context) {
        return;
    }

    if (context->mSession) {
        context->mSession->disconnect();
    }

    if (mOnDisconnected) {
        if (context->mStrand) {
            (void)context->mStrand->enqueue([this, guid]() {
                mOnDisconnected(guid, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
            });
        }
    }
}

void ServerNetworkSystem::receiveLoop(std::stop_token stopToken) {
    while (!stopToken.stop_requested() && mRunning.load(std::memory_order_acquire)) {
        const auto tickBegin = std::chrono::steady_clock::now();

        while (detail::RakPacketOwner packet{mPeer.get(), mPeer->Receive()}) {
            processIncomingPacket(packet.get());
        }

        const auto nextTick = tickBegin + RECEIVE_TICK_INTERVAL;
        const auto now      = std::chrono::steady_clock::now();
        if (now < nextTick) {
            std::this_thread::sleep_until(nextTick);
        }
    }
}

void ServerNetworkSystem::flushLoop(std::stop_token stopToken) {
    std::size_t cursor = 0;

    while (!stopToken.stop_requested() && mRunning.load(std::memory_order_acquire)) {
        const auto tickBegin = std::chrono::steady_clock::now();
        const auto now       = std::chrono::steady_clock::now();

        std::vector<std::shared_ptr<Session>> sessions;
        sessions.reserve(mSessionContexts.size());
        mSessionContexts.for_each([&sessions](const SessionContextsMap::value_type& entry) {
            if (entry.second && entry.second->mSession) {
                sessions.push_back(entry.second->mSession);
            }
        });

        const auto total  = sessions.size();
        const auto budget = flushBudgetPerTick(total);

        for (std::size_t i = 0; i < budget; ++i) {
            if (total == 0) {
                break;
            }

            const auto index   = (cursor + i) % total;
            auto&      session = sessions[index];
            if (!session || !session->isConnected()) {
                continue;
            }

            (void)session->flushIfDue(now);
        }

        if (total > 0) {
            cursor = (cursor + budget) % total;
        }

        const auto nextTick = tickBegin + FLUSH_TICK_INTERVAL;
        const auto current  = std::chrono::steady_clock::now();
        if (current < nextTick) {
            std::this_thread::sleep_until(nextTick);
        }
    }
}

void ServerNetworkSystem::processIncomingPacket(RakNet::Packet* packet) {
    if (!packet || !packet->data || packet->length == 0) {
        return;
    }

    const auto messageId = packet->data[0];
    const auto key       = packet->guid;

    if (messageId == DefaultMessageIDTypes::ID_UNCONNECTED_PING) {
        return;
    }

    if (messageId == DefaultMessageIDTypes::ID_NEW_INCOMING_CONNECTION) {
        auto remote       = RakNet::AddressOrGUID{packet};
        auto context      = std::make_shared<SessionContext>();
        context->mSession = std::make_shared<Session>(mPeer.get(), remote);
        context->mStrand  = std::make_shared<thread::TaskStrand>(mThreadPool);
        upsertSessionContext(key, context);

        if (mOnConnected) {
            (void)context->mStrand->enqueue([this, guid = packet->guid, address = packet->systemAddress]() {
                mOnConnected(guid, address);
            });
        }
        return;
    }

    if (messageId == DefaultMessageIDTypes::ID_DISCONNECTION_NOTIFICATION
        || messageId == DefaultMessageIDTypes::ID_CONNECTION_LOST) {

        auto context = removeSessionContext(key);
        if (context && context->mSession) {
            context->mSession->disconnect();
        }

        if (mOnDisconnected && context && context->mStrand) {
            (void)context->mStrand->enqueue([this, guid = packet->guid, address = packet->systemAddress]() {
                mOnDisconnected(guid, address);
            });
        }
        return;
    }

    if (messageId != MINECRAFT_BATCH_PACKET_ID || packet->length <= 1) {
        return;
    }

    auto context = getSessionContext(packet->guid);
    if (!context || !context->mSession || !context->mStrand) {
        return;
    }

    auto& session = context->mSession;
    auto& strand  = context->mStrand;

    const auto* payloadBegin = reinterpret_cast<const std::byte*>(packet->data + 1);
    const auto  payloadSize  = static_cast<std::size_t>(packet->length - 1);

    auto packets = session->deserializeBatchPackets(std::span<const std::byte>{payloadBegin, payloadSize});
    if (!packets) {
        return;
    }

    for (auto& payload : *packets) {
        if (mOnPacketReceive) {
            auto packetExpected = MinecraftPackets::readAndCreatePacketFromBuffer(payload);
            if (packetExpected) {
                (void)strand->enqueue([this,
                                       guid    = packet->guid,
                                       address = packet->systemAddress,
                                       packet  = std::move(*packetExpected)]() mutable {
                    mOnPacketReceive(guid, address, std::move(packet));
                });
            } else {
                if (mOnPacketParseFailed) {
                    (void)strand->enqueue([this,
                                           guid         = packet->guid,
                                           address      = packet->systemAddress,
                                           packet       = std::move(payload),
                                           errorMessage = std::string(packetExpected.error().mMessage)]() mutable {
                        mOnPacketParseFailed(guid, address, std::move(packet), errorMessage);
                    });
                }
            }
        } else {
            (void)session->enqueueInboundPacket(std::move(payload));
        }
    }
}

void ServerNetworkSystem::upsertSessionContext(const RakNet::RakNetGUID& key, std::shared_ptr<SessionContext> context) {
    mSessionContexts.lazy_emplace_l(
        key,
        [&context](SessionContextsMap::value_type& existing) { existing.second = context; },
        [key, &context](const auto& ctor) { ctor(key, context); }
    );
}

std::shared_ptr<ServerNetworkSystem::SessionContext>
ServerNetworkSystem::removeSessionContext(const RakNet::RakNetGUID& key) {
    std::shared_ptr<SessionContext> removed;
    const bool                      found =
        mSessionContexts.modify_if(key, [&removed](SessionContextsMap::value_type& entry) { removed = entry.second; });
    if (!found) {
        return nullptr;
    }

    (void)mSessionContexts.erase(key);
    return removed;
}

void ServerNetworkSystem::RakPeerDeleter::operator()(RakNet::RakPeerInterface* peer) const noexcept {
    if (peer) {
        RakNet::RakPeerInterface::DestroyInstance(peer);
    }
}

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
