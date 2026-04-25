// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/transaction/ItemReleaseInventoryTransaction.hpp"

namespace sculk::protocol::inline abi_v944 {

void ItemReleaseInventoryTransaction::write(BinaryStream& stream) const {
    stream.writeEnum(mActionType, &BinaryStream::writeUnsignedVarInt);
    stream.writeVarInt(mSlot);
    mItem.write(stream);
    mFromPos.write(stream);
}

Result<> ItemReleaseInventoryTransaction::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mActionType, &ReadOnlyBinaryStream::readUnsignedVarInt); !status) return status;
    if (auto status = stream.readVarInt(mSlot); !status) return status;
    if (auto status = mItem.read(stream); !status) return status;
    return mFromPos.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
