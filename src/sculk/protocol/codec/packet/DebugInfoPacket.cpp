// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/DebugInfoPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds DebugInfoPacket::getId() const noexcept { return MinecraftPacketIds::DebugInfo; }

std::string_view DebugInfoPacket::getName() const noexcept { return "DebugInfoPacket"; }

void DebugInfoPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mActorUniqueId);
    stream.writeString(mData);
}

Result<> DebugInfoPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mActorUniqueId); !status) return status;
    return stream.readString(mData);
}

} // namespace sculk::protocol::inline abi_v944
