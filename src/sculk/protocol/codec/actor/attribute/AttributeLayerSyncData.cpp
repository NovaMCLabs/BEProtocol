// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/actor/attribute/AttributeLayerSyncData.hpp"

namespace sculk::protocol::inline abi_v944 {

void AttributeLayerSyncData::write(BinaryStream& stream) const {
    stream.writeVariantIndex<std::uint32_t>(mData, &BinaryStream::writeUnsignedVarInt);
    std::visit([&](const auto& value) { value.write(stream); }, mData);
}

Result<> AttributeLayerSyncData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVariantIndex<std::uint32_t>(mData, &ReadOnlyBinaryStream::readUnsignedVarInt); !status)
        return status;
    return std::visit([&](auto& value) { return value.read(stream); }, mData);
}

} // namespace sculk::protocol::inline abi_v944
