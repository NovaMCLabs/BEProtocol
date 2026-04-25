// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/actor/attribute/AttributeData.hpp"

namespace sculk::protocol::inline abi_v944 {

void AttributeData::write(BinaryStream& stream) const {
    stream.writeVariantIndex<std::uint32_t>(mData, &BinaryStream::writeUnsignedVarInt);
    std::visit([&stream](const auto& data) { data.write(stream); }, mData);
}

Result<> AttributeData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVariantIndex<std::uint32_t>(mData, &ReadOnlyBinaryStream::readUnsignedVarInt); !status)
        return status;
    return std::visit([&stream](auto& data) { return data.read(stream); }, mData);
}

} // namespace sculk::protocol::inline abi_v944
