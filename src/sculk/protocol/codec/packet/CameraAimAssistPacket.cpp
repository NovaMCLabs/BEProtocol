// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CameraAimAssistPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds CameraAimAssistPacket::getId() const noexcept { return MinecraftPacketIds::CameraAimAssist; }

std::string_view CameraAimAssistPacket::getName() const noexcept { return "CameraAimAssistPacket"; }

void CameraAimAssistPacket::write(BinaryStream& stream) const {
    stream.writeString(mPresetId);
    mViewAngle.write(stream);
    stream.writeFloat(mDistance);
    stream.writeEnum(mTargetMode, &BinaryStream::writeByte);
    stream.writeEnum(mAction, &BinaryStream::writeByte);
    stream.writeBool(mShowDebugRender);
}

Result<> CameraAimAssistPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mPresetId));
    _SCULK_READ(mViewAngle.read(stream));
    _SCULK_READ(stream.readFloat(mDistance));
    _SCULK_READ(stream.readEnum(mTargetMode, &ReadOnlyBinaryStream::readByte));
    _SCULK_READ(stream.readEnum(mAction, &ReadOnlyBinaryStream::readByte));
    return stream.readBool(mShowDebugRender);
}

} // namespace sculk::protocol::inline abi_v975
