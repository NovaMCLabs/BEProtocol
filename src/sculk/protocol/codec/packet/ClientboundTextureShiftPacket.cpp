// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientboundTextureShiftPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ClientboundTextureShiftPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientboundTextureShift;
}

std::string_view ClientboundTextureShiftPacket::getName() const noexcept { return "ClientboundTextureShiftPacket"; }

void ClientboundTextureShiftPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mActionType, &BinaryStream::writeByte);
    stream.writeString(mCollectionName);
    stream.writeString(mFromStep);
    stream.writeString(mToStep);
    stream.writeArray(mAllSteps, &BinaryStream::writeString);
    stream.writeUnsignedVarInt64(mCurrentLengthInTicks);
    stream.writeUnsignedVarInt64(mTotalLengthInTicks);
    stream.writeBool(mIsEnabled);
}

Result<> ClientboundTextureShiftPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mActionType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readString(mCollectionName); !status) return status;
    if (auto status = stream.readString(mFromStep); !status) return status;
    if (auto status = stream.readString(mToStep); !status) return status;
    if (auto status = stream.readArray(mAllSteps, &ReadOnlyBinaryStream::readString); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mCurrentLengthInTicks); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mTotalLengthInTicks); !status) return status;
    return stream.readBool(mIsEnabled);
}

} // namespace sculk::protocol::inline abi_v944
