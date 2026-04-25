// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetActorDataPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SetActorDataPacket::getId() const noexcept { return MinecraftPacketIds::SetActorData; }

std::string_view SetActorDataPacket::getName() const noexcept { return "SetActorDataPacket"; }

void SetActorDataPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    mMetaData.write(stream);
    mSynchedProperties.write(stream);
    stream.writeUnsignedVarInt64(mTick);
}

Result<> SetActorDataPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedVarInt64(mActorRuntimeId));
    _SCULK_READ(mMetaData.read(stream));
    _SCULK_READ(mSynchedProperties.read(stream));
    return stream.readUnsignedVarInt64(mTick);
}

} // namespace sculk::protocol::inline abi_v975
