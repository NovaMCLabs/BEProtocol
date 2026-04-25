// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientboundMapItemDataPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ClientboundMapItemDataPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientboundMapItemData;
}

std::string_view ClientboundMapItemDataPacket::getName() const noexcept { return "ClientboundMapItemDataPacket"; }

void ClientboundMapItemDataPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mMapId);
    stream.writeEnum(mTypeFlag, &BinaryStream::writeUnsignedVarInt);
    stream.writeByte(mDimension);
    stream.writeBool(mIsLockedMap);
    mMapOrigin.write(stream);
    if (static_cast<bool>(mTypeFlag & ClientboundMapItemDataType::Creation)) {
        stream.writeArray(mMapEntries, &BinaryStream::writeVarInt64);
    }
    if (static_cast<bool>(mTypeFlag & ClientboundMapItemDataType::All)) {
        stream.writeByte(mScale);
    }
    if (static_cast<bool>(mTypeFlag & ClientboundMapItemDataType::DecorationUpdate)) {
        stream.writeArray(mTrackedActors, &MapTrackedActorUniqueId::write);
        stream.writeArray(mDecorationList, &MapDecoration::write);
    }
    if (static_cast<bool>(mTypeFlag & ClientboundMapItemDataType::TextureUpdate)) {
        stream.writeVarInt(mTextureWidth);
        stream.writeVarInt(mTextureHeight);
        stream.writeVarInt(mXTexCoordinate);
        stream.writeVarInt(mYTexCoordinate);
        stream.writeArray(mPixels, &BinaryStream::writeUnsignedVarInt);
    }
}

Result<> ClientboundMapItemDataPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mMapId); !status) return status;
    if (auto status = stream.readEnum(mTypeFlag, &ReadOnlyBinaryStream::readUnsignedVarInt); !status) return status;
    if (auto status = stream.readByte(mDimension); !status) return status;
    if (auto status = stream.readBool(mIsLockedMap); !status) return status;
    if (auto status = mMapOrigin.read(stream); !status) return status;
    if (static_cast<bool>(mTypeFlag & ClientboundMapItemDataType::Creation)) {
        if (auto status = stream.readArray(mMapEntries, &ReadOnlyBinaryStream::readVarInt64); !status) return status;
    }
    if (static_cast<bool>(mTypeFlag & ClientboundMapItemDataType::All)) {
        if (auto status = stream.readByte(mScale); !status) return status;
    }
    if (static_cast<bool>(mTypeFlag & ClientboundMapItemDataType::DecorationUpdate)) {
        if (auto status = stream.readArray(mTrackedActors, &MapTrackedActorUniqueId::read); !status) return status;
        if (auto status = stream.readArray(mDecorationList, &MapDecoration::read); !status) return status;
    }
    if (static_cast<bool>(mTypeFlag & ClientboundMapItemDataType::TextureUpdate)) {
        if (auto status = stream.readVarInt(mTextureWidth); !status) return status;
        if (auto status = stream.readVarInt(mTextureHeight); !status) return status;
        if (auto status = stream.readVarInt(mXTexCoordinate); !status) return status;
        if (auto status = stream.readVarInt(mYTexCoordinate); !status) return status;
        if (auto status = stream.readArray(mPixels, &ReadOnlyBinaryStream::readUnsignedVarInt); !status) return status;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
