// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/transaction/InventoryTransactionAction.hpp"

namespace sculk::protocol::inline abi_v944 {

void InventoryTransactionAction::write(BinaryStream& stream) const {
    mSource.write(stream);
    stream.writeUnsignedVarInt(mSlot);
    mFromItem.write(stream);
    mToItem.write(stream);
}

Result<> InventoryTransactionAction::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mSource.read(stream); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mSlot); !status) return status;
    if (auto status = mFromItem.read(stream); !status) return status;
    return mToItem.read(stream);
}

void InventoryTransactionActions::write(BinaryStream& stream) const {
    stream.writeArray(mActions, &InventoryTransactionAction::write);
}

Result<> InventoryTransactionActions::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mActions, &InventoryTransactionAction::read);
}

} // namespace sculk::protocol::inline abi_v944
