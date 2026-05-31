// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, you can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "Pump.hpp"
#include "sculk/protocol/connection/ClientNetworkSystem.hpp"
#include "sculk/protocol/connection/ServerNetworkSystem.hpp"
#include "sculk/protocol/connection/Session.hpp"
#include <concepts>
#include <cstddef>
#include <utility>
#include <vector>

namespace sculk::protocol::inline abi_v975::coro {

template <typename Sink, typename OnStop = std::nullptr_t>
    requires std::invocable<Sink&, std::vector<std::byte>&&>
inline void startSessionReceivePump(coro::Scheduler& scheduler, Session& session, Sink sink, OnStop onStop = nullptr) {
    startPacketPump(
        scheduler,
        [&session]() -> coro::Task<Result<std::vector<std::byte>>> { co_return co_await session.receivePacketAsync(); },
        std::move(sink),
        std::move(onStop)
    );
}

template <typename Sink, typename OnStop = std::nullptr_t>
    requires std::invocable<Sink&, std::vector<std::byte>&&>
inline void
startClientReceivePump(coro::Scheduler& scheduler, ClientNetworkSystem& client, Sink sink, OnStop onStop = nullptr) {
    startPacketPump(
        scheduler,
        [&client]() -> coro::Task<Result<std::vector<std::byte>>> { co_return co_await client.receivePacketAsync(); },
        std::move(sink),
        std::move(onStop)
    );
}

template <typename Sink, typename OnStop = std::nullptr_t>
    requires std::invocable<Sink&, std::vector<std::byte>&&>
inline void startServerReceivePump(
    coro::Scheduler&     scheduler,
    ServerNetworkSystem& server,
    RakNet::RakNetGUID   guid,
    Sink                 sink,
    OnStop               onStop = nullptr
) {
    startPacketPump(
        scheduler,
        [&server, guid]() -> coro::Task<Result<std::vector<std::byte>>> {
            co_return co_await server.receiveFromClientAsync(guid);
        },
        std::move(sink),
        std::move(onStop)
    );
}

} // namespace sculk::protocol::inline abi_v975::coro
