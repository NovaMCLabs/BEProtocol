// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateEquipPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UpdateEquipPacket::getId() const noexcept { return MinecraftPacketIds::UpdateEquip; }

std::string_view UpdateEquipPacket::getName() const noexcept { return "UpdateEquipPacket"; }

void UpdateEquipPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mContainerId, &BinaryStream::writeByte);
    stream.writeEnum(mContainerType, &BinaryStream::writeByte);
    stream.writeVarInt(mSize);
    stream.writeVarInt64(mEntityUniqueId);
    mTag.write(stream);
}

Result<> UpdateEquipPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mContainerId, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readEnum(mContainerType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readVarInt(mSize); !status) return status;
    if (auto status = stream.readVarInt64(mEntityUniqueId); !status) return status;
    return mTag.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
