// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlayerUpdateEntityOverridesPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PlayerUpdateEntityOverridesPacket::getId() const noexcept {
    return MinecraftPacketIds::PlayerUpdateEntityOverrides;
}

std::string_view PlayerUpdateEntityOverridesPacket::getName() const noexcept {
    return "PlayerUpdateEntityOverridesPacket";
}

void PlayerUpdateEntityOverridesPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mId);
    stream.writeUnsignedVarInt(mPropertyIndex);
    stream.writeEnum(mUpdateType, &BinaryStream::writeByte);
    std::visit(
        Overload{
            [&](std::monostate) {},
            [&](std::int32_t value) { stream.writeSignedInt(value); },
            [&](float value) { stream.writeFloat(value); },
        },
        mValue
    );
}

Result<> PlayerUpdateEntityOverridesPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mId); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mPropertyIndex); !status) return status;
    if (auto status = stream.readEnum(mUpdateType, &ReadOnlyBinaryStream::readByte); !status) return status;
    switch (mUpdateType) {
    case UpdateType::SetIntOverride: {
        std::int32_t value{};
        if (auto status = stream.readSignedInt(value); !status) return status;
        mValue = value;
        break;
    }
    case UpdateType::SetFloatOverride: {
        float value{};
        if (auto status = stream.readFloat(value); !status) return status;
        mValue = value;
        break;
    }
    default:
        mValue = std::monostate{};
        break;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
