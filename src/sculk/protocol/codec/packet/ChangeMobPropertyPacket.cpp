// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ChangeMobPropertyPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ChangeMobPropertyPacket::getId() const noexcept { return MinecraftPacketIds::ChangeMobProperty; }

std::string_view ChangeMobPropertyPacket::getName() const noexcept { return "ChangeMobPropertyPacket"; }

void ChangeMobPropertyPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mActorUniqueId);
    stream.writeString(mPropertyName);
    stream.writeBool(mBoolVaue);
    stream.writeString(mStringValue);
    stream.writeVarInt(mIntValue);
    stream.writeFloat(mFloatValue);
}

Result<> ChangeMobPropertyPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mActorUniqueId); !status) return status;
    if (auto status = stream.readString(mPropertyName); !status) return status;
    if (auto status = stream.readBool(mBoolVaue); !status) return status;
    if (auto status = stream.readString(mStringValue); !status) return status;
    if (auto status = stream.readVarInt(mIntValue); !status) return status;
    return stream.readFloat(mFloatValue);
}

} // namespace sculk::protocol::inline abi_v944
