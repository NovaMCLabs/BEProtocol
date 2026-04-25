// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/actor/attribute/AttributeLayerSettings.hpp"

namespace sculk::protocol::inline abi_v944 {

void AttributeLayerWeight::write(BinaryStream& stream) const {
    stream.writeVariantIndex<std::uint32_t>(mWeight, &BinaryStream::writeUnsignedVarInt);
    std::visit(
        Overload{
            [&](float value) { stream.writeFloat(value); },
            [&](const std::string& value) { stream.writeString(value); },
        },
        mWeight
    );
}

Result<> AttributeLayerWeight::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVariantIndex<std::uint32_t>(mWeight, &ReadOnlyBinaryStream::readUnsignedVarInt);
        !status)
        return status;
    return std::visit(
        Overload{
            [&](float& value) { return stream.readFloat(value); },
            [&](std::string& value) { return stream.readString(value); },
        },
        mWeight
    );
}

void AttributeLayerSettings::write(BinaryStream& stream) const {
    stream.writeSignedInt(mPriority);
    mWeight.write(stream);
    stream.writeBool(mEnabled);
    stream.writeBool(mTransitionsPaused);
}

Result<> AttributeLayerSettings::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedInt(mPriority); !status) return status;
    if (auto status = mWeight.read(stream); !status) return status;
    if (auto status = stream.readBool(mEnabled); !status) return status;
    return stream.readBool(mTransitionsPaused);
}

} // namespace sculk::protocol::inline abi_v944
