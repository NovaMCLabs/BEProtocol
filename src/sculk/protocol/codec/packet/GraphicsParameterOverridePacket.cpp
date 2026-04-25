// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/GraphicsParameterOverridePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds GraphicsParameterOverridePacket::getId() const noexcept {
    return MinecraftPacketIds::GraphicsParameterOverride;
}
std::string_view GraphicsParameterOverridePacket::getName() const noexcept { return "GraphicsParameterOverridePacket"; }

void GraphicsParameterOverridePacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(static_cast<std::uint32_t>(mParameterKeyFrameValues.size()));
    for (const auto& [key, value] : mParameterKeyFrameValues) {
        stream.writeFloat(key);
        value.write(stream);
    }
    stream.writeFloat(mFloatValue);
    mVec3Value.write(stream);
    stream.writeString(mBiomeIdentifier);
    stream.writeEnum(mParameterType, &BinaryStream::writeByte);
    stream.writeBool(mResetParameter);
}

Result<> GraphicsParameterOverridePacket::read(ReadOnlyBinaryStream& stream) {
    std::uint32_t mapSize{};
    if (auto status = stream.readUnsignedVarInt(mapSize); !status) return status;
    mParameterKeyFrameValues.clear();
    for (std::uint32_t i = 0; i < mapSize; ++i) {
        float key{};
        Vec3  value{};
        if (auto status = stream.readFloat(key); !status) return status;
        if (auto status = value.read(stream); !status) return status;
        mParameterKeyFrameValues.emplace(std::move(key), std::move(value));
    }
    if (auto status = stream.readFloat(mFloatValue); !status) return status;
    if (auto status = mVec3Value.read(stream); !status) return status;
    if (auto status = stream.readString(mBiomeIdentifier); !status) return status;
    if (auto status = stream.readEnum(mParameterType, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readBool(mResetParameter);
}

} // namespace sculk::protocol::inline abi_v944
