// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AnimatePacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds AnimatePacket::getId() const noexcept { return MinecraftPacketIds::Animate; }

std::string_view AnimatePacket::getName() const noexcept { return "AnimatePacket"; }

void AnimatePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mAction, &BinaryStream::writeByte);
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeFloat(mData);
    stream.writeOptional(mSwingSource, &BinaryStream::writeString);
}

Result<> AnimatePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mAction, &ReadOnlyBinaryStream::readByte));
    _SCULK_READ(stream.readUnsignedVarInt64(mActorRuntimeId));
    _SCULK_READ(stream.readFloat(mData));
    return stream.readOptional(mSwingSource, &ReadOnlyBinaryStream::readString);
}

} // namespace sculk::protocol::inline abi_v975
