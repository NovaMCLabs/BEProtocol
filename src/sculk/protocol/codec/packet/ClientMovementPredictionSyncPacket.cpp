// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientMovementPredictionSyncPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ClientMovementPredictionSyncPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientMovementPredictionSync;
}
std::string_view ClientMovementPredictionSyncPacket::getName() const noexcept {
    return "ClientMovementPredictionSyncPacket";
}

void ClientMovementPredictionSyncPacket::write(BinaryStream& stream) const {
    stream.writeBitset(mActorFlags);
    mActorBoundingBox.write(stream);
    stream.writeFloat(mMovementAttributes.mMovementSpeed);
    stream.writeFloat(mMovementAttributes.mUnderwaterMovementSpeed);
    stream.writeFloat(mMovementAttributes.mLavaMovementSpeed);
    stream.writeFloat(mMovementAttributes.mJumpStrength);
    stream.writeFloat(mMovementAttributes.mHealth);
    stream.writeFloat(mMovementAttributes.mHunger);
    stream.writeVarInt64(mActorID);
    stream.writeBool(mFlying);
}

Result<> ClientMovementPredictionSyncPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readBitset(mActorFlags));
    _SCULK_READ(mActorBoundingBox.read(stream));
    _SCULK_READ(stream.readFloat(mMovementAttributes.mMovementSpeed));
    _SCULK_READ(stream.readFloat(mMovementAttributes.mUnderwaterMovementSpeed));
    _SCULK_READ(stream.readFloat(mMovementAttributes.mLavaMovementSpeed));
    _SCULK_READ(stream.readFloat(mMovementAttributes.mJumpStrength));
    _SCULK_READ(stream.readFloat(mMovementAttributes.mHealth));
    _SCULK_READ(stream.readFloat(mMovementAttributes.mHunger));
    _SCULK_READ(stream.readVarInt64(mActorID));
    return stream.readBool(mFlying);
}

} // namespace sculk::protocol::inline abi_v975
