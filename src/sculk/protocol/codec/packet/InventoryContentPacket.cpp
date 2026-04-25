// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/InventoryContentPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds InventoryContentPacket::getId() const noexcept { return MinecraftPacketIds::InventoryContent; }

std::string_view InventoryContentPacket::getName() const noexcept { return "InventoryContentPacket"; }

void InventoryContentPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(mInventoryId);
    stream.writeArray(mSlots, &NetworkItemStackDescriptor::write);
    mFullContainerName.write(stream);
    mStorageItem.write(stream);
}

Result<> InventoryContentPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt(mInventoryId); !status) return status;
    if (auto status = stream.readArray(mSlots, &NetworkItemStackDescriptor::read); !status) return status;
    if (auto status = mFullContainerName.read(stream); !status) return status;
    return mStorageItem.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
