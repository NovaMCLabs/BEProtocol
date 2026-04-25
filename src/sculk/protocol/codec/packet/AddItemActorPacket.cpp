// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AddItemActorPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

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
    if (auto status = stream.readVarInt64(mUniqueId); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mRuntimeId); !status) return status;
    if (auto status = mItem.read(stream); !status) return status;
    if (auto status = mPos.read(stream); !status) return status;
    if (auto status = mVelocity.read(stream); !status) return status;
    if (auto status = mMetaData.read(stream); !status) return status;
    return stream.readBool(mIsFromFishing);
}

} // namespace sculk::protocol::inline abi_v944
