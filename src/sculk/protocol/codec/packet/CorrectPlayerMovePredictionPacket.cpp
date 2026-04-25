// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CorrectPlayerMovePredictionPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds CorrectPlayerMovePredictionPacket::getId() const noexcept {
    return MinecraftPacketIds::CorrectPlayerMovePrediction;
}

std::string_view CorrectPlayerMovePredictionPacket::getName() const noexcept {
    return "CorrectPlayerMovePredictionPacket";
}

void CorrectPlayerMovePredictionPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mPredictionType, &BinaryStream::writeByte);
    mPos.write(stream);
    mPosDelta.write(stream);
    mVehiclePrediction.write(stream);
    stream.writeOptional(mVehicleAngularVelocity, &BinaryStream::writeFloat);
    stream.writeBool(mOnGround);
    stream.writeUnsignedVarInt64(mPlayerInputTick);
}

Result<> CorrectPlayerMovePredictionPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mPredictionType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = mPos.read(stream); !status) return status;
    if (auto status = mPosDelta.read(stream); !status) return status;
    if (auto status = mVehiclePrediction.read(stream); !status) return status;
    if (auto status = stream.readOptional(mVehicleAngularVelocity, &ReadOnlyBinaryStream::readFloat); !status)
        return status;
    if (auto status = stream.readBool(mOnGround); !status) return status;
    return stream.readUnsignedVarInt64(mPlayerInputTick);
}

} // namespace sculk::protocol::inline abi_v944
