// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateBlockSyncedPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UpdateBlockSyncedPacket::getId() const noexcept { return MinecraftPacketIds::UpdateBlockSynced; }

std::string_view UpdateBlockSyncedPacket::getName() const noexcept { return "UpdateBlockSyncedPacket"; }

void UpdateBlockSyncedPacket::write(BinaryStream& stream) const {
    mBlockPosition.write(stream);
    stream.writeUnsignedVarInt(mRuntimeId);
    stream.writeUnsignedVarInt(mFlag);
    stream.writeUnsignedVarInt(mLayer);
    stream.writeUnsignedVarInt64(mUniqueActorId);
    stream.writeUnsignedVarInt64(mActorSyncMessage);
}

Result<> UpdateBlockSyncedPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mBlockPosition.read(stream); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mRuntimeId); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mFlag); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mLayer); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mUniqueActorId); !status) return status;
    return stream.readUnsignedVarInt64(mActorSyncMessage);
}

} // namespace sculk::protocol::inline abi_v944
