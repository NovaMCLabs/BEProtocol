// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/MoveActorDeltaPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

namespace {

constexpr std::uint16_t HasX       = 1u << 0;
constexpr std::uint16_t HasY       = 1u << 1;
constexpr std::uint16_t HasZ       = 1u << 2;
constexpr std::uint16_t HasPitch   = 1u << 3;
constexpr std::uint16_t HasYaw     = 1u << 4;
constexpr std::uint16_t HasHeadYaw = 1u << 5;

} // namespace

MinecraftPacketIds MoveActorDeltaPacket::getId() const noexcept { return MinecraftPacketIds::MoveActorDelta; }

std::string_view MoveActorDeltaPacket::getName() const noexcept { return "MoveActorDeltaPacket"; }

void MoveActorDeltaPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeUnsignedShort(mHeader);
    if ((mHeader & HasX) != 0) {
        stream.writeFloat(mNewPosX);
    }
    if ((mHeader & HasY) != 0) {
        stream.writeFloat(mNewPosY);
    }
    if ((mHeader & HasZ) != 0) {
        stream.writeFloat(mNewPosZ);
    }
    if ((mHeader & HasPitch) != 0) {
        stream.writeByte(mRotationXByteAngle);
    }
    if ((mHeader & HasYaw) != 0) {
        stream.writeByte(mRotationYByteAngle);
    }
    if ((mHeader & HasHeadYaw) != 0) {
        stream.writeByte(mRotationYHeaderByteAngle);
    }
}

Result<> MoveActorDeltaPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    if (auto status = stream.readUnsignedShort(mHeader); !status) return status;
    if ((mHeader & HasX) != 0) {
        if (auto status = stream.readFloat(mNewPosX); !status) return status;
    }
    if ((mHeader & HasY) != 0) {
        if (auto status = stream.readFloat(mNewPosY); !status) return status;
    }
    if ((mHeader & HasZ) != 0) {
        if (auto status = stream.readFloat(mNewPosZ); !status) return status;
    }
    if ((mHeader & HasPitch) != 0) {
        if (auto status = stream.readByte(mRotationXByteAngle); !status) return status;
    }
    if ((mHeader & HasYaw) != 0) {
        if (auto status = stream.readByte(mRotationYByteAngle); !status) return status;
    }
    if ((mHeader & HasHeadYaw) != 0) {
        if (auto status = stream.readByte(mRotationYHeaderByteAngle); !status) return status;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
