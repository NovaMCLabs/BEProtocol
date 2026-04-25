// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientCacheStatusPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ClientCacheStatusPacket::getId() const noexcept { return MinecraftPacketIds::ClientCacheStatus; }

std::string_view ClientCacheStatusPacket::getName() const noexcept { return "ClientCacheStatusPacket"; }

void ClientCacheStatusPacket::write(BinaryStream& stream) const { stream.writeBool(mIsCacheSupport); }

Result<> ClientCacheStatusPacket::read(ReadOnlyBinaryStream& stream) { return stream.readBool(mIsCacheSupport); }

} // namespace sculk::protocol::inline abi_v944
