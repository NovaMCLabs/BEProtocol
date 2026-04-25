// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/item/ItemStackResponse.hpp"

namespace sculk::protocol::inline abi_v944 {

void ItemStackResponseSlotInfo::write(BinaryStream& stream) const {
    stream.writeByte(mRequestedSlot);
    stream.writeByte(mSlot);
    stream.writeByte(mAmount);
    stream.writeVarInt(mNetId);
    stream.writeString(mCustomName);
    stream.writeString(mFilteredCustomName);
    stream.writeVarInt(mDurationCorrection);
}

Result<> ItemStackResponseSlotInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readByte(mRequestedSlot); !status) return status;
    if (auto status = stream.readByte(mSlot); !status) return status;
    if (auto status = stream.readByte(mAmount); !status) return status;
    if (auto status = stream.readVarInt(mNetId); !status) return status;
    if (auto status = stream.readString(mCustomName); !status) return status;
    if (auto status = stream.readString(mFilteredCustomName); !status) return status;
    return stream.readVarInt(mDurationCorrection);
}

void ItemStackResponseContainerInfo::write(BinaryStream& stream) const {
    mContainerName.write(stream);
    stream.writeArray(mSlots, &ItemStackResponseSlotInfo::write);
}

Result<> ItemStackResponseContainerInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mContainerName.read(stream); !status) return status;
    return stream.readArray(mSlots, &ItemStackResponseSlotInfo::read);
}

void ItemStackResponseInfo::write(BinaryStream& stream) const {
    stream.writeEnum(mResult, &BinaryStream::writeByte);
    stream.writeVarInt(mRequestId);
    if (mResult == ItemStackNetResult::Success) {
        stream.writeArray(mContainers, &ItemStackResponseContainerInfo::write);
    }
}

Result<> ItemStackResponseInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mResult, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readVarInt(mRequestId); !status) return status;
    if (mResult == ItemStackNetResult::Success) {
        return stream.readArray(mContainers, &ItemStackResponseContainerInfo::read);
    }
    return {};
}

void ItemStackResponse::write(BinaryStream& stream) const {
    stream.writeArray(mResponses, &ItemStackResponseInfo::write);
}

Result<> ItemStackResponse::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mResponses, &ItemStackResponseInfo::read);
}

} // namespace sculk::protocol::inline abi_v944
