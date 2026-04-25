// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AddPaintingPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds AddPaintingPacket::getId() const noexcept { return MinecraftPacketIds::AddPainting; }

std::string_view AddPaintingPacket::getName() const noexcept { return "AddPaintingPacket"; }

void AddPaintingPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mUniqueId);
    stream.writeUnsignedVarInt64(mRuntimeId);
    mPosition.write(stream);
    stream.writeVarInt(mDirection);
    stream.writeString(mMotif);
}

Result<> AddPaintingPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mUniqueId); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mRuntimeId); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = stream.readVarInt(mDirection); !status) return status;
    return stream.readString(mMotif);
}

} // namespace sculk::protocol::inline abi_v944
