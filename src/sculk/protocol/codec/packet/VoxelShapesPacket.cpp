// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/VoxelShapesPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void VoxelShapesPacket::RegistryHandle::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeUnsignedShort(mValue);
}

Result<> VoxelShapesPacket::RegistryHandle::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    return stream.readUnsignedShort(mValue);
}

MinecraftPacketIds VoxelShapesPacket::getId() const noexcept { return MinecraftPacketIds::VoxelShapes; }

std::string_view VoxelShapesPacket::getName() const noexcept { return "VoxelShapesPacket"; }

void VoxelShapesPacket::write(BinaryStream& stream) const {
    stream.writeArray(mShapes, &SerializableVoxelShape::write);
    stream.writeArray(mRegistryHandles, &RegistryHandle::write);
    stream.writeUnsignedShort(mCustomShapeCount);
}

Result<> VoxelShapesPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readArray(mShapes, &SerializableVoxelShape::read); !status) return status;
    if (auto status = stream.readArray(mRegistryHandles, &RegistryHandle::read); !status) return status;
    return stream.readUnsignedShort(mCustomShapeCount);
}

} // namespace sculk::protocol::inline abi_v944
