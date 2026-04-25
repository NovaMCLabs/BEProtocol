// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/RemoveVolumeEntityPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds RemoveVolumeEntityPacket::getId() const noexcept { return MinecraftPacketIds::RemoveVolumeEntity; }

std::string_view RemoveVolumeEntityPacket::getName() const noexcept { return "RemoveVolumeEntityPacket"; }

void RemoveVolumeEntityPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(mEntityNetId);
    stream.writeVarInt(mDimensionType);
}

Result<> RemoveVolumeEntityPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt(mEntityNetId); !status) return status;
    return stream.readVarInt(mDimensionType);
}

} // namespace sculk::protocol::inline abi_v944
