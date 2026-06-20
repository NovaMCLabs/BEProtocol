// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetScorePacket.hpp"
#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
#include "../utility/Format.hpp"
#endif

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

void SetScorePacket::ScoreInfo::write(BinaryStream& stream, PacketType type) const {
    stream.writeVarInt64(mScoreboardId);
    stream.writeString(mObjectiveName);
    stream.writeSignedInt(mScoreValue);
    if (type == PacketType::Change) {
        stream.writeEnum(mIdentityType, &BinaryStream::writeByte);
        switch (mIdentityType) {
        case IdentityType::Player:
        case IdentityType::Entity:
            stream.writeVarInt64(mActorUniqueId);
            break;
        case IdentityType::FakePlayer:
            stream.writeString(mFakePlayerName);
            break;
        default:
            break;
        }
    }
}

Result<> SetScorePacket::ScoreInfo::read(ReadOnlyBinaryStream& stream, PacketType type) {
    _SCULK_READ(stream.readVarInt64(mScoreboardId));
    _SCULK_READ(stream.readString(mObjectiveName));
    _SCULK_READ(stream.readSignedInt(mScoreValue));
    if (type == PacketType::Change) {
        _SCULK_READ(stream.readEnum(mIdentityType, &ReadOnlyBinaryStream::readByte));
        switch (mIdentityType) {
        case IdentityType::Player:
        case IdentityType::Entity:
            _SCULK_READ(stream.readVarInt64(mActorUniqueId));
            break;
        case IdentityType::FakePlayer:
            _SCULK_READ(stream.readString(mFakePlayerName));
            break;
        default:
            break;
        }
    }
    return {};
}

MinecraftPacketIds SetScorePacket::getId() const noexcept { return MinecraftPacketIds::SetScore; }

std::string_view SetScorePacket::getName() const noexcept { return "SetScorePacket"; }

void SetScorePacket::write(BinaryStream& stream) const {
    stream.writeEnum(mPacketType, &BinaryStream::writeByte);
    stream.writeArray(
        mScoresInfo,
        &BinaryStream::writeUnsignedVarInt,
        [this](BinaryStream& stream, const ScoreInfo& info) { info.write(stream, mPacketType); }
    );
}

Result<> SetScorePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mPacketType, &ReadOnlyBinaryStream::readByte));
    return stream.readArray(
        mScoresInfo,
        &ReadOnlyBinaryStream::readUnsignedVarInt,
        [this](ReadOnlyBinaryStream& stream, ScoreInfo& info) { return info.read(stream, mPacketType); }
    );
}

#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
std::string SetScorePacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mPacketType), SCULK_FORMAT_FIELD(mScoresInfo));
}
#endif

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
