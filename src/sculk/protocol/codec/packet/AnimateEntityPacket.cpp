// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AnimateEntityPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds AnimateEntityPacket::getId() const noexcept { return MinecraftPacketIds::AnimateEntity; }

std::string_view AnimateEntityPacket::getName() const noexcept { return "AnimateEntityPacket"; }

void AnimateEntityPacket::write(BinaryStream& stream) const {
    stream.writeString(mAnimation);
    stream.writeString(mNextState);
    stream.writeString(mStopExpression);
    stream.writeEnum(mStopExpressionMolangVersion, &BinaryStream::writeSignedInt);
    stream.writeString(mController);
    stream.writeFloat(mBlendOutTime);
    stream.writeArray(mRuntimeIds, &BinaryStream::writeUnsignedVarInt64);
}

Result<> AnimateEntityPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mAnimation));
    _SCULK_READ(stream.readString(mNextState));
    _SCULK_READ(stream.readString(mStopExpression));
    _SCULK_READ(stream.readEnum(mStopExpressionMolangVersion, &ReadOnlyBinaryStream::readSignedInt));
    _SCULK_READ(stream.readString(mController));
    _SCULK_READ(stream.readFloat(mBlendOutTime));
    return stream.readArray(mRuntimeIds, &ReadOnlyBinaryStream::readUnsignedVarInt64);
}

} // namespace sculk::protocol::inline abi_v975
