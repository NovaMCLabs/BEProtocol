// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/BossEventPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds BossEventPacket::getId() const noexcept { return MinecraftPacketIds::BossEvent; }

std::string_view BossEventPacket::getName() const noexcept { return "BossEventPacket"; }

void BossEventPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mTargetActor);
    stream.writeEnum(mType, &BinaryStream::writeUnsignedVarInt);
    switch (mType) {
    case EventType::Add:
        stream.writeString(mName);
        stream.writeString(mFilteredName);
        stream.writeFloat(mPercentage);
        stream.writeUnsignedShort(mDarkenScreen);
        stream.writeUnsignedVarInt(mColor);
        stream.writeUnsignedVarInt(mOverlay);
        break;
    case EventType::PlayerAdded:
    case EventType::PlayerRemoved:
    case EventType::Query:
        stream.writeVarInt64(mPlayer);
        break;
    case EventType::UpdatePercent:
        stream.writeFloat(mPercentage);
        break;
    case EventType::UpdateName:
        stream.writeString(mName);
        stream.writeString(mFilteredName);
        break;
    case EventType::UpdateProperties:
        stream.writeUnsignedShort(mDarkenScreen);
        stream.writeUnsignedVarInt(mColor);
        stream.writeUnsignedVarInt(mOverlay);
        break;
    case EventType::UpdateStyle:
        stream.writeUnsignedVarInt(mColor);
        stream.writeUnsignedVarInt(mOverlay);
        break;
    default:
        break;
    }
}

Result<> BossEventPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mTargetActor); !status) return status;
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readUnsignedVarInt); !status) return status;
    switch (mType) {
    case EventType::Add:
        if (auto status = stream.readString(mName); !status) return status;
        if (auto status = stream.readString(mFilteredName); !status) return status;
        if (auto status = stream.readFloat(mPercentage); !status) return status;
        if (auto status = stream.readUnsignedShort(mDarkenScreen); !status) return status;
        if (auto status = stream.readUnsignedVarInt(mColor); !status) return status;
        return stream.readUnsignedVarInt(mOverlay);
    case EventType::PlayerAdded:
    case EventType::PlayerRemoved:
    case EventType::Query:
        return stream.readVarInt64(mPlayer);
    case EventType::UpdatePercent:
        return stream.readFloat(mPercentage);
    case EventType::UpdateName:
        if (auto status = stream.readString(mName); !status) return status;
        return stream.readString(mFilteredName);
    case EventType::UpdateProperties:
        if (auto status = stream.readUnsignedShort(mDarkenScreen); !status) return status;
        if (auto status = stream.readUnsignedVarInt(mColor); !status) return status;
        return stream.readUnsignedVarInt(mOverlay);
    case EventType::UpdateStyle:
        if (auto status = stream.readUnsignedVarInt(mColor); !status) return status;
        return stream.readUnsignedVarInt(mOverlay);
    default:
        return {};
    }
}

} // namespace sculk::protocol::inline abi_v944
