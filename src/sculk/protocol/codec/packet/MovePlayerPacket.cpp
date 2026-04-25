// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/MovePlayerPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds MovePlayerPacket::getId() const noexcept { return MinecraftPacketIds::MovePlayer; }
std::string_view   MovePlayerPacket::getName() const noexcept { return "MovePlayerPacket"; }

void MovePlayerPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    mPosition.write(stream);
    mRotation.write(stream);
    stream.writeFloat(mYHeadRotation);
    stream.writeEnum(mPositionMode, &BinaryStream::writeByte);
    stream.writeBool(mOnGround);
    stream.writeUnsignedVarInt64(mRidingRuntimeId);
    if (mPositionMode == PositionMode::Teleport) {
        stream.writeSignedInt(mTeleportationCause);
        stream.writeSignedInt(mSourceActorType);
    }
    stream.writeUnsignedVarInt64(mTick);
}

Result<> MovePlayerPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = mRotation.read(stream); !status) return status;
    if (auto status = stream.readFloat(mYHeadRotation); !status) return status;
    if (auto status = stream.readEnum(mPositionMode, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readBool(mOnGround); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mRidingRuntimeId); !status) return status;
    if (mPositionMode == PositionMode::Teleport) {
        if (auto status = stream.readSignedInt(mTeleportationCause); !status) return status;
        if (auto status = stream.readSignedInt(mSourceActorType); !status) return status;
    }
    return stream.readUnsignedVarInt64(mTick);
}

} // namespace sculk::protocol::inline abi_v944
