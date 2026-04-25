// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlayerAuthInputPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PlayerAuthInputPacket::getId() const noexcept { return MinecraftPacketIds::PlayerAuthInput; }

std::string_view PlayerAuthInputPacket::getName() const noexcept { return "PlayerAuthInputPacket"; }

void PlayerAuthInputPacket::write(BinaryStream& stream) const {
    mPlayerRotation.write(stream);
    mPosition.write(stream);
    mMoveVector.write(stream);
    stream.writeFloat(mPlayerHeadRotation);
    stream.writeBitset(mInputData);
    static_assert(mInputData.size() == PLAYER_AUTH_INPUT_DATA_COUNT);
    stream.writeUnsignedVarInt(mInputType);
    stream.writeUnsignedVarInt(mPlayMode);
    stream.writeUnsignedVarInt(mNewInteractionModel);
    mInteractRotation.write(stream);
    stream.writeUnsignedVarInt64(mClientTick);
    mPosDelta.write(stream);
    if (mInputData.test(static_cast<std::size_t>(PlayerAuthInputData::PerformItemInteraction))) {
        mItemUseTransaction.write(stream);
    }
    if (mInputData.test(static_cast<std::size_t>(PlayerAuthInputData::PerformItemStackRequest))) {
        mItemStackRequestData.write(stream);
    }
    if (mInputData.test(static_cast<std::size_t>(PlayerAuthInputData::PerformBlockActions))) {
        mPlayerBlockActions.write(stream);
    }
    if (mInputData.test(static_cast<std::size_t>(PlayerAuthInputData::IsInClientPredictedVehicle))) {
        mVehicleRotation.write(stream);
        stream.writeVarInt64(mClientPredictedVihicle);
    }
    mAnologMoveVector.write(stream);
    mCameraOrientation.write(stream);
    mRawMoveVector.write(stream);
}

Result<> PlayerAuthInputPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mPlayerRotation.read(stream); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = mMoveVector.read(stream); !status) return status;
    if (auto status = stream.readFloat(mPlayerHeadRotation); !status) return status;
    if (auto status = stream.readBitset(mInputData); !status) return status;
    static_assert(mInputData.size() == PLAYER_AUTH_INPUT_DATA_COUNT);
    if (auto status = stream.readUnsignedVarInt(mInputType); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mPlayMode); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mNewInteractionModel); !status) return status;
    if (auto status = mInteractRotation.read(stream); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mClientTick); !status) return status;
    if (auto status = mPosDelta.read(stream); !status) return status;
    if (mInputData.test(static_cast<std::size_t>(PlayerAuthInputData::PerformItemInteraction))) {
        if (auto status = mItemUseTransaction.read(stream); !status) return status;
    }
    if (mInputData.test(static_cast<std::size_t>(PlayerAuthInputData::PerformItemStackRequest))) {
        if (auto status = mItemStackRequestData.read(stream); !status) return status;
    }
    if (mInputData.test(static_cast<std::size_t>(PlayerAuthInputData::PerformBlockActions))) {
        if (auto status = mPlayerBlockActions.read(stream); !status) return status;
    }
    if (mInputData.test(static_cast<std::size_t>(PlayerAuthInputData::IsInClientPredictedVehicle))) {
        if (auto status = mVehicleRotation.read(stream); !status) return status;
        if (auto status = stream.readVarInt64(mClientPredictedVihicle); !status) return status;
    }
    if (auto status = mAnologMoveVector.read(stream); !status) return status;
    if (auto status = mCameraOrientation.read(stream); !status) return status;
    return mRawMoveVector.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
