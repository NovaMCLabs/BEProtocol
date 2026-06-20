// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/transaction/InventoryTransactionSource.hpp"

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

void InventoryTransactionSource::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeUnsignedVarInt);
    stream.writeOptional(mContainerId, [&](BinaryStream& stream, const std::uint8_t& value) {
        if (mType == InventoryTransactionSourceType::ContainerInventory
            || mType == InventoryTransactionSourceType::NonImplementedFeatureTODO) {
            stream.writeBool(true);
            stream.writeByte(value);
        } else {
            stream.writeBool(false);
        }
    });
    stream.writeOptional(mBitFlags, [&](BinaryStream& stream, std::uint32_t const& value) {
        if (mType == InventoryTransactionSourceType::WorldInteraction) {
            stream.writeBool(true);
            stream.writeUnsignedVarInt(value);
        } else {
            stream.writeBool(false);
        }
    });
}

Result<> InventoryTransactionSource::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mType, &ReadOnlyBinaryStream::readUnsignedVarInt));
    bool hasContainerId{};
    bool shouldWriteContainerId{};
    _SCULK_READ(stream.readBool(hasContainerId));
    _SCULK_READ(stream.readBool(shouldWriteContainerId));
    if (hasContainerId && shouldWriteContainerId) {
        _SCULK_READ(stream.readByte(mContainerId.emplace()));
    }
    bool hasBitFlags{};
    bool shouldWriteBitFlags{};
    _SCULK_READ(stream.readBool(hasBitFlags));
    _SCULK_READ(stream.readBool(shouldWriteBitFlags));
    if (hasBitFlags && shouldWriteBitFlags) {
        _SCULK_READ(stream.readUnsignedVarInt(mBitFlags.emplace()));
    }
    return {};
}

void InventoryTransactionSource::writeLegacy(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeUnsignedVarInt);
    switch (mType) {
    case InventoryTransactionSourceType::ContainerInventory:
    case InventoryTransactionSourceType::NonImplementedFeatureTODO:
        stream.writeVarInt(mContainerId.value_or(0));
        break;
    case InventoryTransactionSourceType::WorldInteraction:
        stream.writeUnsignedVarInt(mBitFlags.value_or(0));
        break;
    default:
        break;
    }
}

Result<> InventoryTransactionSource::readLegacy(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readEnum(mType, &ReadOnlyBinaryStream::readUnsignedVarInt));
    switch (mType) {
    case InventoryTransactionSourceType::ContainerInventory:
    case InventoryTransactionSourceType::NonImplementedFeatureTODO: {
        int containerId{};
        _SCULK_READ(stream.readVarInt(containerId));
        mContainerId.emplace() = static_cast<std::uint8_t>(containerId);
        return {};
    }
    case InventoryTransactionSourceType::WorldInteraction: {
        return stream.readUnsignedVarInt(mBitFlags.emplace());
    }
    default:
        return {};
    }
}

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE