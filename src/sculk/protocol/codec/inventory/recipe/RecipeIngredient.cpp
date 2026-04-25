// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/recipe/RecipeIngredient.hpp"

namespace sculk::protocol::inline abi_v944 {

void RecipeIngredient::write(BinaryStream& stream) const {
    stream.writeVariantIndex<std::uint8_t>(mDescriptor, &BinaryStream::writeByte);
    std::visit(
        Overload{
            [&](const InternalItemDescriptor& descriptor) {
                stream.writeSignedShort(descriptor.mId);
                if (descriptor.mId != 0) {
                    stream.writeSignedShort(descriptor.mAux);
                }
            },
            [&](const MolangDescriptor& descriptor) {
                stream.writeString(descriptor.mMolangFullName);
                stream.writeByte(descriptor.mMolangVersion);
            },
            [&](const ItemTagDescriptor& descriptor) { stream.writeString(descriptor.mItemTag); },
            [&](const DeferredDescriptor& descriptor) {
                stream.writeString(descriptor.mDeferredFullName);
                stream.writeUnsignedShort(descriptor.mAux);
            },
            [&](const ComplexAliasDescriptor& descriptor) { stream.writeString(descriptor.mName); },
            [&](const std::monostate&) {}
        },
        mDescriptor
    );
    stream.writeVarInt(mStackSize);
}

Result<> RecipeIngredient::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVariantIndex<std::uint8_t>(mDescriptor, &ReadOnlyBinaryStream::readByte); !status)
        return status;
    if (auto status = std::visit(
            Overload{
                [&](InternalItemDescriptor& descriptor) {
                    if (auto status = stream.readSignedShort(descriptor.mId); !status) return status;
                    if (descriptor.mId != 0) {
                        if (auto status = stream.readSignedShort(descriptor.mAux); !status) return status;
                    }
                    return Result<>{};
                },
                [&](MolangDescriptor& descriptor) {
                    if (auto status = stream.readString(descriptor.mMolangFullName); !status) return status;
                    return stream.readByte(descriptor.mMolangVersion);
                },
                [&](ItemTagDescriptor& descriptor) { return stream.readString(descriptor.mItemTag); },
                [&](DeferredDescriptor& descriptor) {
                    if (auto status = stream.readString(descriptor.mDeferredFullName); !status) return status;
                    return stream.readUnsignedShort(descriptor.mAux);
                },
                [&](ComplexAliasDescriptor& descriptor) { return stream.readString(descriptor.mName); },
                [&](std::monostate&) { return Result<>{}; }
            },
            mDescriptor
        );
        !status) {
        return status;
    }
    return stream.readVarInt(mStackSize);
}

} // namespace sculk::protocol::inline abi_v944
