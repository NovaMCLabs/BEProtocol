// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/transaction/ItemUseInventoryTransaction.hpp"

namespace sculk::protocol::inline abi_v944 {

void ItemUseInventoryTransaction::write(BinaryStream& stream) const {
    stream.writeEnum(mActionType, &BinaryStream::writeUnsignedVarInt);
    stream.writeEnum(mTriggerType, &BinaryStream::writeUnsignedVarInt);
    mPos.write(stream);
    stream.writeVarInt(mFace);
    stream.writeVarInt(mSlot);
    mItem.write(stream);
    mFromPos.write(stream);
    mClickPos.write(stream);
    stream.writeUnsignedVarInt(mTargetBlockId);
    stream.writeEnum(mClientPredictedResult, &BinaryStream::writeByte);
    stream.writeEnum(mClientCooldownState, &BinaryStream::writeByte);
}

Result<> ItemUseInventoryTransaction::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mActionType, &ReadOnlyBinaryStream::readUnsignedVarInt); !status) return status;
    if (auto status = stream.readEnum(mTriggerType, &ReadOnlyBinaryStream::readUnsignedVarInt); !status) return status;
    if (auto status = mPos.read(stream); !status) return status;
    if (auto status = stream.readVarInt(mFace); !status) return status;
    if (auto status = stream.readVarInt(mSlot); !status) return status;
    if (auto status = mItem.read(stream); !status) return status;
    if (auto status = mFromPos.read(stream); !status) return status;
    if (auto status = mClickPos.read(stream); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mTargetBlockId); !status) return status;
    if (auto status = stream.readEnum(mClientPredictedResult, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readEnum(mClientCooldownState, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
