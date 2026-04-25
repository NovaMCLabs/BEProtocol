// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/MotionPredictionHintsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds MotionPredictionHintsPacket::getId() const noexcept {
    return MinecraftPacketIds::MotionPredictionHints;
}

std::string_view MotionPredictionHintsPacket::getName() const noexcept { return "MotionPredictionHintsPacket"; }

void MotionPredictionHintsPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    mMotion.write(stream);
    stream.writeBool(mOnGround);
}

Result<> MotionPredictionHintsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    if (auto status = mMotion.read(stream); !status) return status;
    return stream.readBool(mOnGround);
}

} // namespace sculk::protocol::inline abi_v944
