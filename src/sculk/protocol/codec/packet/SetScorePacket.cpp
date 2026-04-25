// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetScorePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SetScorePacket::getId() const noexcept { return MinecraftPacketIds::SetScore; }

std::string_view SetScorePacket::getName() const noexcept { return "SetScorePacket"; }

void SetScorePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mPacketType, &BinaryStream::writeByte);
    stream.writeUnsignedVarInt(static_cast<std::uint32_t>(mScoresInfo.size()));
    for (const auto& info : mScoresInfo) {
        stream.writeVarInt64(info.mScoreboardId);
        stream.writeString(info.mObjectiveName);
        stream.writeSignedInt(info.mScoreValue);
        if (mPacketType == PacketType::Change) {
            stream.writeEnum(info.mIdentityType, &BinaryStream::writeByte);
            switch (info.mIdentityType) {
            case IdentityType::Player:
            case IdentityType::Entity:
                stream.writeVarInt64(info.mActorUniqueId);
                break;
            case IdentityType::FakePlayer:
                stream.writeString(info.mFakePlayerName);
                break;
            default:
                break;
            }
        }
    }
}

Result<> SetScorePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mPacketType, &ReadOnlyBinaryStream::readByte); !status) return status;
    std::uint32_t count{};
    if (auto status = stream.readUnsignedVarInt(count); !status) return status;
    mScoresInfo.clear();
    mScoresInfo.resize(count);
    for (auto& info : mScoresInfo) {
        if (auto status = stream.readVarInt64(info.mScoreboardId); !status) return status;
        if (auto status = stream.readString(info.mObjectiveName); !status) return status;
        if (auto status = stream.readSignedInt(info.mScoreValue); !status) return status;
        if (mPacketType == PacketType::Change) {
            if (auto status = stream.readEnum(info.mIdentityType, &ReadOnlyBinaryStream::readByte); !status)
                return status;
            switch (info.mIdentityType) {
            case IdentityType::Player:
            case IdentityType::Entity:
                if (auto status = stream.readVarInt64(info.mActorUniqueId); !status) return status;
                break;
            case IdentityType::FakePlayer:
                if (auto status = stream.readString(info.mFakePlayerName); !status) return status;
                break;
            default:
                break;
            }
        }
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
