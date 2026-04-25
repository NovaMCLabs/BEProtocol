// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlayerToggleCrafterSlotRequestPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PlayerToggleCrafterSlotRequestPacket::getId() const noexcept {
    return MinecraftPacketIds::PlayerToggleCrafterSlotRequest;
}

std::string_view PlayerToggleCrafterSlotRequestPacket::getName() const noexcept {
    return "PlayerToggleCrafterSlotRequestPacket";
}

void PlayerToggleCrafterSlotRequestPacket::write(BinaryStream& stream) const {
    stream.writeSignedInt(mPosX);
    stream.writeSignedInt(mPosY);
    stream.writeSignedInt(mPosZ);
    stream.writeByte(mSlotIndex);
    stream.writeBool(mIsDisabled);
}

Result<> PlayerToggleCrafterSlotRequestPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedInt(mPosX); !status) return status;
    if (auto status = stream.readSignedInt(mPosY); !status) return status;
    if (auto status = stream.readSignedInt(mPosZ); !status) return status;
    if (auto status = stream.readByte(mSlotIndex); !status) return status;
    return stream.readBool(mIsDisabled);
}

} // namespace sculk::protocol::inline abi_v944
