// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SubChunkPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void SubChunkPacket::SubChunkPosOffset::write(BinaryStream& stream) const {
    stream.writeSignedChar(mX);
    stream.writeSignedChar(mY);
    stream.writeSignedChar(mZ);
}

Result<> SubChunkPacket::SubChunkPosOffset::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedChar(mX); !status) return status;
    if (auto status = stream.readSignedChar(mY); !status) return status;
    return stream.readSignedChar(mZ);
}

void SubChunkPacket::HeightmapData::write(BinaryStream& stream) const {
    stream.writeEnum(mHeightMapType, &BinaryStream::writeByte);
    if (mHeightMapType == HeightMapDataType::HasData) {
        stream.writeBytes(&mSubchunkHeightMap, sizeof(mSubchunkHeightMap));
    }
    stream.writeEnum(mRenderHeightMapType, &BinaryStream::writeByte);
    if (mRenderHeightMapType == HeightMapDataType::HasData) {
        stream.writeBytes(&mRenderHeightMap, sizeof(mRenderHeightMap));
    }
}

Result<> SubChunkPacket::HeightmapData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mHeightMapType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (mHeightMapType == HeightMapDataType::HasData) {
        if (auto status = stream.readBytes(&mSubchunkHeightMap, sizeof(mSubchunkHeightMap)); !status) return status;
    }
    if (auto status = stream.readEnum(mRenderHeightMapType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (mRenderHeightMapType == HeightMapDataType::HasData) {
        if (auto status = stream.readBytes(&mRenderHeightMap, sizeof(mRenderHeightMap)); !status) return status;
    }
    return {};
}

void SubChunkPacket::SubChunkPacketData::write(BinaryStream& stream, bool cacheEnabled) const {
    mSubChunkPosOffset.write(stream);
    stream.writeEnum(mResult, &BinaryStream::writeByte);
    if (!cacheEnabled || mResult != SubChunkRequestResult::SuccessAllAir) {
        stream.writeString(mSerializedSubChunk);
    }
    mHeightMapData.write(stream);
    if (cacheEnabled) {
        stream.writeUnsignedInt64(mBlobId);
    }
}

Result<> SubChunkPacket::SubChunkPacketData::read(ReadOnlyBinaryStream& stream, bool cacheEnabled) {
    if (auto status = mSubChunkPosOffset.read(stream); !status) return status;
    if (auto status = stream.readEnum(mResult, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (!cacheEnabled || mResult != SubChunkRequestResult::SuccessAllAir) {
        if (auto status = stream.readString(mSerializedSubChunk); !status) return status;
    } else {
        mSerializedSubChunk.clear();
    }
    if (auto status = mHeightMapData.read(stream); !status) return status;
    if (cacheEnabled) {
        return stream.readUnsignedInt64(mBlobId);
    }
    return {};
}

MinecraftPacketIds SubChunkPacket::getId() const noexcept { return MinecraftPacketIds::SubChunk; }

std::string_view SubChunkPacket::getName() const noexcept { return "SubChunkPacket"; }

void SubChunkPacket::write(BinaryStream& stream) const {
    stream.writeBool(mCacheEnabled);
    stream.writeVarInt(mDimensionType);
    mCenterPos.write(stream);
    stream.writeUnsignedInt(static_cast<std::uint32_t>(mSubChunkData.size()));
    for (const SubChunkPacketData& data : mSubChunkData) {
        data.write(stream, mCacheEnabled);
    }
}

Result<> SubChunkPacket::read(ReadOnlyBinaryStream& stream) {
    std::uint32_t count{};
    if (auto status = stream.readBool(mCacheEnabled); !status) return status;
    if (auto status = stream.readVarInt(mDimensionType); !status) return status;
    if (auto status = mCenterPos.read(stream); !status) return status;
    if (auto status = stream.readUnsignedInt(count); !status) return status;
    mSubChunkData.resize(count);
    for (SubChunkPacketData& data : mSubChunkData) {
        if (auto status = data.read(stream, mCacheEnabled); !status) return status;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
