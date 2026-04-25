// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/InventorySlotPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds InventorySlotPacket::getId() const noexcept { return MinecraftPacketIds::InventorySlot; }

std::string_view InventorySlotPacket::getName() const noexcept { return "InventorySlotPacket"; }

void InventorySlotPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(mInventoryId);
    stream.writeUnsignedVarInt(mSlot);
    mFullContainerName.write(stream);
    mStorageItem.write(stream);
    mItem.write(stream);
}

Result<> InventorySlotPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt(mInventoryId); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mSlot); !status) return status;
    if (auto status = mFullContainerName.read(stream); !status) return status;
    if (auto status = mStorageItem.read(stream); !status) return status;
    return mItem.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
