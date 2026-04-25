// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/LevelChunkPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds LevelChunkPacket::getId() const noexcept { return MinecraftPacketIds::LevelChunk; }

std::string_view LevelChunkPacket::getName() const noexcept { return "LevelChunkPacket"; }

void LevelChunkPacket::write(BinaryStream& stream) const {
    mPosition.write(stream);
    stream.writeVarInt(mDimensionId);
    if (!mClientNeedsToRequestSubchunks) {
        stream.writeUnsignedVarInt(mSubChunksCount);
    } else if (mClientRequestSubChunkLimit < 0) {
        stream.writeUnsignedVarInt(0xFFFFFFFFu);
    } else {
        stream.writeUnsignedVarInt(0xFFFFFFFEu);
        stream.writeUnsignedShort(static_cast<std::uint16_t>(mClientRequestSubChunkLimit));
    }
    stream.writeBool(mCacheEnabled);
    if (mCacheEnabled) {
        stream.writeArray(mCacheBlobs, &BinaryStream::writeUnsignedInt64);
    }
    stream.writeString(mSerializedChunk);
}

Result<> LevelChunkPacket::read(ReadOnlyBinaryStream& stream) {
    std::uint32_t subChunkHeader{};
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = stream.readVarInt(mDimensionId); !status) return status;
    if (auto status = stream.readUnsignedVarInt(subChunkHeader); !status) return status;

    if (subChunkHeader == 0xFFFFFFFFu) {
        mClientNeedsToRequestSubchunks = true;
        mClientRequestSubChunkLimit    = -1;
        mSubChunksCount                = 0;
    } else if (subChunkHeader == 0xFFFFFFFEu) {
        std::uint16_t limit{};
        if (auto status = stream.readUnsignedShort(limit); !status) return status;
        mClientNeedsToRequestSubchunks = true;
        mClientRequestSubChunkLimit    = static_cast<std::int16_t>(limit);
        mSubChunksCount                = 0;
    } else {
        mClientNeedsToRequestSubchunks = false;
        mSubChunksCount                = subChunkHeader;
        mClientRequestSubChunkLimit    = 0;
    }

    if (auto status = stream.readBool(mCacheEnabled); !status) return status;
    if (mCacheEnabled) {
        if (auto status = stream.readArray(mCacheBlobs, &ReadOnlyBinaryStream::readUnsignedInt64); !status)
            return status;
    } else {
        mCacheBlobs.clear();
    }

    return stream.readString(mSerializedChunk);
}

} // namespace sculk::protocol::inline abi_v944
