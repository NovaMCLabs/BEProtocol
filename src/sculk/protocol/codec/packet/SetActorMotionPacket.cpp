// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetActorMotionPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SetActorMotionPacket::getId() const noexcept { return MinecraftPacketIds::SetActorMotion; }

std::string_view SetActorMotionPacket::getName() const noexcept { return "SetActorMotionPacket"; }

void SetActorMotionPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    mMotion.write(stream);
    stream.writeUnsignedVarInt64(mTick);
}

Result<> SetActorMotionPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedVarInt64(mActorRuntimeId));
    _SCULK_READ(mMotion.read(stream));
    return stream.readUnsignedVarInt64(mTick);
}

} // namespace sculk::protocol::inline abi_v975
