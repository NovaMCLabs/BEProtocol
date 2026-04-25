// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientMovementPredictionSyncPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ClientMovementPredictionSyncPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientMovementPredictionSync;
}
std::string_view ClientMovementPredictionSyncPacket::getName() const noexcept {
    return "ClientMovementPredictionSyncPacket";
}

void ClientMovementPredictionSyncPacket::write(BinaryStream& stream) const {
    stream.writeBitset(mActorFlags);
    static_assert(mActorFlags.size() == ACTOR_FLAGS_COUNT);
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
    if (auto status = stream.readBitset(mActorFlags); !status) return status;
    static_assert(mActorFlags.size() == ACTOR_FLAGS_COUNT);
    if (auto status = mActorBoundingBox.read(stream); !status) return status;
    if (auto status = stream.readFloat(mMovementAttributes.mMovementSpeed); !status) return status;
    if (auto status = stream.readFloat(mMovementAttributes.mUnderwaterMovementSpeed); !status) return status;
    if (auto status = stream.readFloat(mMovementAttributes.mLavaMovementSpeed); !status) return status;
    if (auto status = stream.readFloat(mMovementAttributes.mJumpStrength); !status) return status;
    if (auto status = stream.readFloat(mMovementAttributes.mHealth); !status) return status;
    if (auto status = stream.readFloat(mMovementAttributes.mHunger); !status) return status;
    if (auto status = stream.readVarInt64(mActorID); !status) return status;
    return stream.readBool(mFlying);
}

} // namespace sculk::protocol::inline abi_v944
