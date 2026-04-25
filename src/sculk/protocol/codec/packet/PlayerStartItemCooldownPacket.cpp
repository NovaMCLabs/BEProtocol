// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlayerStartItemCooldownPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PlayerStartItemCooldownPacket::getId() const noexcept {
    return MinecraftPacketIds::PlayerStartItemCooldown;
}

std::string_view PlayerStartItemCooldownPacket::getName() const noexcept { return "PlayerStartItemCooldownPacket"; }

void PlayerStartItemCooldownPacket::write(BinaryStream& stream) const {
    stream.writeString(mItemCategory);
    stream.writeVarInt(mDurationTicks);
}

Result<> PlayerStartItemCooldownPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mItemCategory); !status) return status;
    return stream.readVarInt(mDurationTicks);
}

} // namespace sculk::protocol::inline abi_v944
