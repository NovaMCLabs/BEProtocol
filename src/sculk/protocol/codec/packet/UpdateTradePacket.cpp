// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateTradePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UpdateTradePacket::getId() const noexcept { return MinecraftPacketIds::UpdateTrade; }

std::string_view UpdateTradePacket::getName() const noexcept { return "UpdateTradePacket"; }

void UpdateTradePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mContainerId, &BinaryStream::writeByte);
    stream.writeEnum(mContainerType, &BinaryStream::writeByte);
    stream.writeVarInt(mSize);
    stream.writeVarInt(mTier);
    stream.writeVarInt64(mEntityUniqueId);
    stream.writeVarInt64(mLastTradingPlayer);
    stream.writeString(mDisplayName);
    stream.writeBool(mUseNewTradeScreen);
    stream.writeBool(mUseEconomyTrade);
    mOffers.write(stream);
}

Result<> UpdateTradePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mContainerId, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readEnum(mContainerType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readVarInt(mSize); !status) return status;
    if (auto status = stream.readVarInt(mTier); !status) return status;
    if (auto status = stream.readVarInt64(mEntityUniqueId); !status) return status;
    if (auto status = stream.readVarInt64(mLastTradingPlayer); !status) return status;
    if (auto status = stream.readString(mDisplayName); !status) return status;
    if (auto status = stream.readBool(mUseNewTradeScreen); !status) return status;
    if (auto status = stream.readBool(mUseEconomyTrade); !status) return status;
    return mOffers.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
