// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ServerboundDiagnosticsPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

void ServerboundDiagnosticsPacket::MemoryCategoryCounter::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeByte);
    stream.writeUnsignedInt64(mCurrentBytes);
}

Result<> ServerboundDiagnosticsPacket::MemoryCategoryCounter::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mType, &ReadOnlyBinaryStream::readByte));
    return stream.readUnsignedInt64(mCurrentBytes);
}

void ServerboundDiagnosticsPacket::EntityDiagnosticTimingInfo::write(BinaryStream& stream) const {
    stream.writeString(mDisplayName);
    stream.writeString(mEntity);
    stream.writeUnsignedInt64(mTimeInNanoseconds);
    stream.writeByte(mPercentOfTotal);
}

Result<> ServerboundDiagnosticsPacket::EntityDiagnosticTimingInfo::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mDisplayName));
    _SCULK_READ(stream.readString(mEntity));
    _SCULK_READ(stream.readUnsignedInt64(mTimeInNanoseconds));
    return stream.readByte(mPercentOfTotal);
}

void ServerboundDiagnosticsPacket::SystemDiagnosticTimingInfo::write(BinaryStream& stream) const {
    stream.writeString(mDisplayName);
    stream.writeUnsignedInt64(mSystemIndex);
    stream.writeUnsignedInt64(mTimeInNanoseconds);
    stream.writeByte(mPercentOfTotal);
}

Result<> ServerboundDiagnosticsPacket::SystemDiagnosticTimingInfo::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mDisplayName));
    _SCULK_READ(stream.readUnsignedInt64(mSystemIndex));
    _SCULK_READ(stream.readUnsignedInt64(mTimeInNanoseconds));
    return stream.readByte(mPercentOfTotal);
}

MinecraftPacketIds ServerboundDiagnosticsPacket::getId() const noexcept {
    return MinecraftPacketIds::ServerboundDiagnostics;
}
std::string_view ServerboundDiagnosticsPacket::getName() const noexcept { return "ServerboundDiagnosticsPacket"; }

void ServerboundDiagnosticsPacket::write(BinaryStream& stream) const {
    stream.writeFloat(mAvgFps);
    stream.writeFloat(mAvgServerSimTickTimeMS);
    stream.writeFloat(mAvgClientSimTickTimeMS);
    stream.writeFloat(mAvgBeginFrameTimeMS);
    stream.writeFloat(mAvgInputTimeMS);
    stream.writeFloat(mAvgRenderTimeMS);
    stream.writeFloat(mAvgEndFrameTimeMS);
    stream.writeFloat(mAvgRemainderTimePercent);
    stream.writeFloat(mAvgUnaccountedTimePercent);
    stream.writeArray(mMemoryCategoryValues, &MemoryCategoryCounter::write);
    stream.writeArray(mEntityDiagnostics, &EntityDiagnosticTimingInfo::write);
    stream.writeArray(mSystemDiagnostics, &SystemDiagnosticTimingInfo::write);
}

Result<> ServerboundDiagnosticsPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readFloat(mAvgFps));
    _SCULK_READ(stream.readFloat(mAvgServerSimTickTimeMS));
    _SCULK_READ(stream.readFloat(mAvgClientSimTickTimeMS));
    _SCULK_READ(stream.readFloat(mAvgBeginFrameTimeMS));
    _SCULK_READ(stream.readFloat(mAvgInputTimeMS));
    _SCULK_READ(stream.readFloat(mAvgRenderTimeMS));
    _SCULK_READ(stream.readFloat(mAvgEndFrameTimeMS));
    _SCULK_READ(stream.readFloat(mAvgRemainderTimePercent));
    _SCULK_READ(stream.readFloat(mAvgUnaccountedTimePercent));
    _SCULK_READ(stream.readArray(mMemoryCategoryValues, &MemoryCategoryCounter::read));
    _SCULK_READ(stream.readArray(mEntityDiagnostics, &EntityDiagnosticTimingInfo::read));
    return stream.readArray(mSystemDiagnostics, &SystemDiagnosticTimingInfo::read);
}

} // namespace sculk::protocol::inline abi_v975
