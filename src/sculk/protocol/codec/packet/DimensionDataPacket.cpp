// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/DimensionDataPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void DimensionDataPacket::DimensionDefinition::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeVarInt(mHeightMax);
    stream.writeVarInt(mHeightMin);
    stream.writeVarInt(mGeneratorType);
}

Result<> DimensionDataPacket::DimensionDefinition::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readVarInt(mHeightMax); !status) return status;
    if (auto status = stream.readVarInt(mHeightMin); !status) return status;
    return stream.readVarInt(mGeneratorType);
}

MinecraftPacketIds DimensionDataPacket::getId() const noexcept { return MinecraftPacketIds::DimensionData; }

std::string_view DimensionDataPacket::getName() const noexcept { return "DimensionDataPacket"; }

void DimensionDataPacket::write(BinaryStream& stream) const {
    stream.writeArray(mDefinitionGroup, &DimensionDefinition::write);
}

Result<> DimensionDataPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mDefinitionGroup, &DimensionDefinition::read);
}

} // namespace sculk::protocol::inline abi_v944
