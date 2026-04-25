// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/InventoryTransactionPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds InventoryTransactionPacket::getId() const noexcept {
    return MinecraftPacketIds::InventoryTransaction;
}

std::string_view InventoryTransactionPacket::getName() const noexcept { return "InventoryTransactionPacket"; }

void InventoryTransactionPacket::write(BinaryStream& stream) const {
    stream.writeVarInt(mLegacyRequestRawId);
    if (mLegacyRequestRawId < -1 && (mLegacyRequestRawId & 1) == 0) {
        stream.writeArray(mLegacySetItemSlots, &LegacySetItemSlot::write);
    }
    stream.writeVariantIndex<std::uint32_t>(mTransactionData, &BinaryStream::writeUnsignedVarInt);
    mInventoryTransactionActions.write(stream);
    std::visit([&](const auto& transaction) { transaction.write(stream); }, mTransactionData);
}

Result<> InventoryTransactionPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mLegacyRequestRawId); !status) return status;
    if (mLegacyRequestRawId < -1 && (mLegacyRequestRawId & 1) == 0) {
        if (auto status = stream.readArray(mLegacySetItemSlots, &LegacySetItemSlot::read); !status) return status;
    }
    if (auto status =
            stream.readVariantIndex<std::uint32_t>(mTransactionData, &ReadOnlyBinaryStream::readUnsignedVarInt);
        !status) {
        return status;
    }
    if (auto status = mInventoryTransactionActions.read(stream); !status) return status;
    return std::visit([&](auto& transaction) { return transaction.read(stream); }, mTransactionData);
}

} // namespace sculk::protocol::inline abi_v944
