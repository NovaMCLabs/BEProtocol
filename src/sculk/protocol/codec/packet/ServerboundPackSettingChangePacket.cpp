// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ServerboundPackSettingChangePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ServerboundPackSettingChangePacket::getId() const noexcept {
    return MinecraftPacketIds::ServerboundPackSettingChange;
}

std::string_view ServerboundPackSettingChangePacket::getName() const noexcept {
    return "ServerboundPackSettingChangePacket";
}

void ServerboundPackSettingChangePacket::write(BinaryStream& stream) const {
    mPackId.write(stream);
    stream.writeByte(mPackSettingDataType);
    stream.writeString(mPackSettingName);
    stream.writeBool(mBoolValue);
    stream.writeFloat(mFloatValue);
    stream.writeString(mStringValue);
}

Result<> ServerboundPackSettingChangePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mPackId.read(stream); !status) return status;
    if (auto status = stream.readByte(mPackSettingDataType); !status) return status;
    if (auto status = stream.readString(mPackSettingName); !status) return status;
    if (auto status = stream.readBool(mBoolValue); !status) return status;
    if (auto status = stream.readFloat(mFloatValue); !status) return status;
    return stream.readString(mStringValue);
}

} // namespace sculk::protocol::inline abi_v944
