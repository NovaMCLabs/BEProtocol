// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/RequestAbilityPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds RequestAbilityPacket::getId() const noexcept { return MinecraftPacketIds::RequestAbility; }

std::string_view RequestAbilityPacket::getName() const noexcept { return "RequestAbilityPacket"; }

void RequestAbilityPacket::write(BinaryStream& stream) const {
    stream.writeVarInt(mAbility);
    stream.writeEnum(mType, &BinaryStream::writeByte);
    if (mType != Type::Unset) {
        stream.writeBool(mBoolValue);
        stream.writeFloat(mFloatValue);
    }
}

Result<> RequestAbilityPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mAbility); !status) return status;
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (mType != Type::Unset) {
        if (auto status = stream.readBool(mBoolValue); !status) return status;
        if (auto status = stream.readFloat(mFloatValue); !status) return status;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
