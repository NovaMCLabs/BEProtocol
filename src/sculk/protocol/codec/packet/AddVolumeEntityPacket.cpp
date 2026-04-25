// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AddVolumeEntityPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds AddVolumeEntityPacket::getId() const noexcept { return MinecraftPacketIds::AddVolumeEntity; }

std::string_view AddVolumeEntityPacket::getName() const noexcept { return "AddVolumeEntityPacket"; }

void AddVolumeEntityPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(mEntityNetId);
    mComponents.write(stream);
    stream.writeString(mJsonIdentifier);
    stream.writeString(mInstanceName);
    mMaxBounds.write(stream);
    mMaxBounds.write(stream);
    stream.writeVarInt(mDimensionType);
    stream.writeString(mEngineVersion);
}

Result<> AddVolumeEntityPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt(mEntityNetId); !status) return status;
    if (auto status = mComponents.read(stream); !status) return status;
    if (auto status = stream.readString(mJsonIdentifier); !status) return status;
    if (auto status = stream.readString(mInstanceName); !status) return status;
    if (auto status = mMaxBounds.read(stream); !status) return status;
    if (auto status = mMaxBounds.read(stream); !status) return status;
    if (auto status = stream.readVarInt(mDimensionType); !status) return status;
    return stream.readString(mEngineVersion);
}

} // namespace sculk::protocol::inline abi_v944
