// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AddItemActorPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds AddItemActorPacket::getId() const noexcept { return MinecraftPacketIds::AddItemActor; }

std::string_view AddItemActorPacket::getName() const noexcept { return "AddItemActorPacket"; }

void AddItemActorPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mUniqueId);
    stream.writeUnsignedVarInt64(mRuntimeId);
    mItem.write(stream);
    mPos.write(stream);
    mVelocity.write(stream);
    mMetaData.write(stream);
    stream.writeBool(mIsFromFishing);
}

Result<> AddItemActorPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readVarInt64(mUniqueId));
    _SCULK_READ(stream.readUnsignedVarInt64(mRuntimeId));
    _SCULK_READ(mItem.read(stream));
    _SCULK_READ(mPos.read(stream));
    _SCULK_READ(mVelocity.read(stream));
    _SCULK_READ(mMetaData.read(stream));
    return stream.readBool(mIsFromFishing);
}

} // namespace sculk::protocol::inline abi_v975
