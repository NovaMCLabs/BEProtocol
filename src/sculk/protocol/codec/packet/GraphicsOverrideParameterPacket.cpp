// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/GraphicsOverrideParameterPacket.hpp"
#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
#include "../utility/Format.hpp"
#endif

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

MinecraftPacketIds GraphicsOverrideParameterPacket::getId() const noexcept {
    return MinecraftPacketIds::GraphicsOverrideParameter;
}
std::string_view GraphicsOverrideParameterPacket::getName() const noexcept { return "GraphicsOverrideParameterPacket"; }

void GraphicsOverrideParameterPacket::write(BinaryStream& stream) const {
    stream.writeArray(mParameterKeyFrameValues, [](BinaryStream& stream, const ParameterKeyFrame& keyFrame) {
        stream.writeFloat(keyFrame.mTime);
        keyFrame.mValue.write(stream);
    });
    stream.writeOptional(mFloatValue, &BinaryStream::writeFloat);
    stream.writeOptional(mVec3Value, &Vec3::write);
    stream.writeString(mBiomeIdentifier);
    stream.writeOptional(mPlayerIdentifier, &BinaryStream::writeString);
    stream.writeEnum(mParameterType, &BinaryStream::writeByte);
    stream.writeBool(mResetParameter);
}

Result<> GraphicsOverrideParameterPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(
        stream.readArray(mParameterKeyFrameValues, [](ReadOnlyBinaryStream& stream, ParameterKeyFrame& keyFrame) {
            _SCULK_READ(stream.readFloat(keyFrame.mTime));
            return keyFrame.mValue.read(stream);
        })
    );
    _SCULK_READ(stream.readOptional(mFloatValue, &ReadOnlyBinaryStream::readFloat));
    _SCULK_READ(stream.readOptional(mVec3Value, &Vec3::read));
    _SCULK_READ(stream.readString(mBiomeIdentifier));
    _SCULK_READ(stream.readOptional(mPlayerIdentifier, &ReadOnlyBinaryStream::readString));
    _SCULK_READ(stream.readEnum(mParameterType, &ReadOnlyBinaryStream::readByte));
    return stream.readBool(mResetParameter);
}

#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
std::string GraphicsOverrideParameterPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mParameterKeyFrameValues),
        SCULK_FORMAT_FIELD(mFloatValue),
        SCULK_FORMAT_FIELD(mVec3Value),
        SCULK_FORMAT_FIELD(mBiomeIdentifier),
        SCULK_FORMAT_FIELD(mPlayerIdentifier),
        SCULK_FORMAT_FIELD(mParameterType),
        SCULK_FORMAT_FIELD(mResetParameter)
    );
}
#endif

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
