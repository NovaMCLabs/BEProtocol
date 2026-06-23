// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/Version.hpp"
#include <RakPeerInterface.h>
#include <utility>

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE::detail {

class RakPacketOwner final {
public:
    RakPacketOwner() = default;

    RakPacketOwner(RakNet::RakPeerInterface* peer, RakNet::Packet* packet) noexcept : mPeer(peer), mPacket(packet) {}

    RakPacketOwner(const RakPacketOwner&)            = delete;
    RakPacketOwner& operator=(const RakPacketOwner&) = delete;

    RakPacketOwner(RakPacketOwner&& other) noexcept
    : mPeer(std::exchange(other.mPeer, nullptr)),
      mPacket(std::exchange(other.mPacket, nullptr)) {}

    RakPacketOwner& operator=(RakPacketOwner&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        reset();
        mPeer   = std::exchange(other.mPeer, nullptr);
        mPacket = std::exchange(other.mPacket, nullptr);
        return *this;
    }

    ~RakPacketOwner() { reset(); }

public:
    [[nodiscard]] RakNet::Packet* get() const noexcept { return mPacket; }

    [[nodiscard]] explicit operator bool() const noexcept { return mPacket != nullptr; }

    [[nodiscard]] RakNet::Packet* operator->() const noexcept { return mPacket; }

    void reset() noexcept {
        if (mPeer && mPacket) {
            mPeer->DeallocatePacket(mPacket);
        }

        mPeer   = nullptr;
        mPacket = nullptr;
    }

private:
    RakNet::RakPeerInterface* mPeer{nullptr};
    RakNet::Packet*           mPacket{nullptr};
};

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE::detail
