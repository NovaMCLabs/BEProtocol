// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlayerListPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void PlayerListEntry::write(BinaryStream& stream) const {
    mUUID.write(stream);
    stream.writeVarInt64(mActorUniqueId);
    stream.writeString(mPlayerName);
    stream.writeString(mXuid);
    stream.writeString(mPlatformChatId);
    stream.writeSignedInt(mBuildPlatform);
    mSerializedSkin.write(stream);
    stream.writeBool(mIsTeacher);
    stream.writeBool(mIsHost);
    stream.writeBool(mIsSubClient);
    stream.writeSignedInt(mColor);
}

Result<> PlayerListEntry::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mUUID.read(stream); !status) return status;
    if (auto status = stream.readVarInt64(mActorUniqueId); !status) return status;
    if (auto status = stream.readString(mPlayerName); !status) return status;
    if (auto status = stream.readString(mXuid); !status) return status;
    if (auto status = stream.readString(mPlatformChatId); !status) return status;
    if (auto status = stream.readSignedInt(mBuildPlatform); !status) return status;
    if (auto status = mSerializedSkin.read(stream); !status) return status;
    if (auto status = stream.readBool(mIsTeacher); !status) return status;
    if (auto status = stream.readBool(mIsHost); !status) return status;
    if (auto status = stream.readBool(mIsSubClient); !status) return status;
    return stream.readSignedInt(mColor);
}

MinecraftPacketIds PlayerListPacket::getId() const noexcept { return MinecraftPacketIds::PlayerList; }

std::string_view PlayerListPacket::getName() const noexcept { return "PlayerListPacket"; }

void PlayerListPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mAction, &BinaryStream::writeByte);
    stream.writeUnsignedVarInt(static_cast<std::uint32_t>(mPlayerEntryList.size()));
    if (mAction == ActionType::Add) {
        for (const PlayerListEntry& entry : mPlayerEntryList) {
            entry.write(stream);
        }
        for (const PlayerListEntry& entry : mPlayerEntryList) {
            stream.writeBool(entry.mSkinTrusted);
        }
    } else {
        for (const PlayerListEntry& entry : mPlayerEntryList) {
            entry.mUUID.write(stream);
        }
    }
}

Result<> PlayerListPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mAction, &ReadOnlyBinaryStream::readByte); !status) return status;
    std::uint32_t entryCount{};
    if (auto status = stream.readUnsignedVarInt(entryCount); !status) return status;
    mPlayerEntryList.resize(entryCount);
    if (mAction == ActionType::Add) {
        for (PlayerListEntry& entry : mPlayerEntryList) {
            if (auto status = entry.read(stream); !status) return status;
        }
        for (PlayerListEntry& entry : mPlayerEntryList) {
            if (auto status = stream.readBool(entry.mSkinTrusted); !status) return status;
        }
    } else {
        for (PlayerListEntry& entry : mPlayerEntryList) {
            if (auto status = entry.mUUID.read(stream); !status) return status;
        }
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
