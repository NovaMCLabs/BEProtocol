// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/transaction/InventoryTransaction.hpp"

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

void InventoryTransactionAction::write(BinaryStream& stream) const {
    mSource.write(stream);
    stream.writeUnsignedVarInt(mSlot);
    mFromItem.writeCereal(stream);
    mToItem.writeCereal(stream);
}

Result<> InventoryTransactionAction::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(mSource.read(stream));
    _SCULK_READ(stream.readUnsignedVarInt(mSlot));
    _SCULK_READ(mFromItem.readCereal(stream));
    return mToItem.readCereal(stream);
}

void InventoryTransactionAction::writeLegacy(BinaryStream& stream) const {
    mSource.writeLegacy(stream);
    stream.writeUnsignedVarInt(mSlot);
    mFromItem.write(stream);
    mToItem.write(stream);
}

Result<> InventoryTransactionAction::readLegacy(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(mSource.readLegacy(stream));
    _SCULK_READ(stream.readUnsignedVarInt(mSlot));
    _SCULK_READ(mFromItem.read(stream));
    return mToItem.read(stream);
}

void InventoryTransaction::write(BinaryStream& stream) const {
    stream.writeArray(mActions, &InventoryTransactionAction::write);
}

Result<> InventoryTransaction::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mActions, &InventoryTransactionAction::read);
}

void InventoryTransaction::writeLegacy(BinaryStream& stream) const {
    stream.writeArray(mActions, &InventoryTransactionAction::writeLegacy);
}

Result<> InventoryTransaction::readLegacy(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mActions, &InventoryTransactionAction::readLegacy);
}

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
