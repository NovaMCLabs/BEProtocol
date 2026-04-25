// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/actor/attribute/ColorAttributeData.hpp"

namespace sculk::protocol::inline abi_v944 {

void Color255RGBAData::write(BinaryStream& stream) const {
    stream.writeVariantIndex<std::uint32_t>(mColor, &BinaryStream::writeUnsignedVarInt);
    std::visit(
        Overload{
            [&](const std::string& value) { stream.writeString(value); },
            [&](const std::array<int32_t, 4>& value) {
                for (auto channel : value) {
                    stream.writeSignedInt(channel);
                }
            },
        },
        mColor
    );
}

Result<> Color255RGBAData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVariantIndex<std::uint32_t>(mColor, &ReadOnlyBinaryStream::readUnsignedVarInt);
        !status)
        return status;
    return std::visit(
        Overload{
            [&](std::string& value) { return stream.readString(value); },
            [&](std::array<int32_t, 4>& value) {
                for (auto& channel : value) {
                    if (auto status = stream.readSignedInt(channel); !status) return status;
                }
                return Result<>{};
            },
        },
        mColor
    );
}

void ColorAttributeData::write(BinaryStream& stream) const {
    mValue.write(stream);
    stream.writeEnum(mOperation, &BinaryStream::writeSignedInt);
}

Result<> ColorAttributeData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mValue.read(stream); !status) return status;
    return stream.readEnum(mOperation, &ReadOnlyBinaryStream::readSignedInt);
}

} // namespace sculk::protocol::inline abi_v944
