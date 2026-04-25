// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/MoveActorAbsolutePacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds MoveActorAbsolutePacket::getId() const noexcept { return MinecraftPacketIds::MoveActorAbsolute; }

std::string_view MoveActorAbsolutePacket::getName() const noexcept { return "MoveActorAbsolutePacket"; }

void MoveActorAbsolutePacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeByte(mHeader);
    mPosition.write(stream);
    stream.writeByte(mRotationX);
    stream.writeByte(mRotationY);
    stream.writeByte(mRotationYHead);
    stream.writeBool(mForceCompletion);
}

Result<> MoveActorAbsolutePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedVarInt64(mActorRuntimeId));
    _SCULK_READ(stream.readByte(mHeader));
    _SCULK_READ(mPosition.read(stream));
    _SCULK_READ(stream.readByte(mRotationX));
    _SCULK_READ(stream.readByte(mRotationY));
    _SCULK_READ(stream.readByte(mRotationYHead));
    return stream.readBool(mForceCompletion);
}

} // namespace sculk::protocol::inline abi_v975
