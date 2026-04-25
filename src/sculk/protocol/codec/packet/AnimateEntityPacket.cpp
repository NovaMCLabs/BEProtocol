// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AnimateEntityPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

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
    if (auto status = stream.readString(mAnimation); !status) return status;
    if (auto status = stream.readString(mNextState); !status) return status;
    if (auto status = stream.readString(mStopExpression); !status) return status;
    if (auto status = stream.readEnum(mStopExpressionMolangVersion, &ReadOnlyBinaryStream::readSignedInt); !status)
        return status;
    if (auto status = stream.readString(mController); !status) return status;
    if (auto status = stream.readFloat(mBlendOutTime); !status) return status;
    return stream.readArray(mRuntimeIds, &ReadOnlyBinaryStream::readUnsignedVarInt64);
}

} // namespace sculk::protocol::inline abi_v944
