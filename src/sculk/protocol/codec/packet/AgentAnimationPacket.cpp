// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AgentAnimationPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds AgentAnimationPacket::getId() const noexcept { return MinecraftPacketIds::AgentAnimation; }

std::string_view AgentAnimationPacket::getName() const noexcept { return "AgentAnimationPacket"; }

void AgentAnimationPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mAnimation, &BinaryStream::writeByte);
    stream.writeUnsignedVarInt64(mRuntimeId);
}

Result<> AgentAnimationPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mAnimation, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readUnsignedVarInt64(mRuntimeId);
}

} // namespace sculk::protocol::inline abi_v944
