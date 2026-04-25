// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateBlockPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UpdateBlockPacket::getId() const noexcept { return MinecraftPacketIds::UpdateBlock; }

std::string_view UpdateBlockPacket::getName() const noexcept { return "UpdateBlockPacket"; }

void UpdateBlockPacket::write(BinaryStream& stream) const {
    mBlockPosition.write(stream);
    stream.writeUnsignedVarInt(mRuntimeId);
    stream.writeUnsignedVarInt(mFlag);
    stream.writeUnsignedVarInt(mLayer);
}

Result<> UpdateBlockPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mBlockPosition.read(stream); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mRuntimeId); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mFlag); !status) return status;
    return stream.readUnsignedVarInt(mLayer);
}

} // namespace sculk::protocol::inline abi_v944
