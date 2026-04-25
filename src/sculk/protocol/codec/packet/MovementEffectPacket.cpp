// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/MovementEffectPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds MovementEffectPacket::getId() const noexcept { return MinecraftPacketIds::MovementEffect; }

std::string_view MovementEffectPacket::getName() const noexcept { return "MovementEffectPacket"; }

void MovementEffectPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeEnum(mEffectId, &BinaryStream::writeVarInt);
    stream.writeVarInt(mEffectDuration);
    stream.writeUnsignedVarInt64(mTick);
}

Result<> MovementEffectPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    if (auto status = stream.readEnum(mEffectId, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readVarInt(mEffectDuration); !status) return status;
    return stream.readUnsignedVarInt64(mTick);
}

} // namespace sculk::protocol::inline abi_v944
