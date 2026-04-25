// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/enchant/EnchantOption.hpp"

namespace sculk::protocol::inline abi_v944 {

void Enchant::write(BinaryStream& stream) const {
    stream.writeByte(mType);
    stream.writeByte(mLevel);
}

Result<> Enchant::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readByte(mType); !status) return status;
    return stream.readByte(mLevel);
}

void ItemEnchants::write(BinaryStream& stream) const {
    stream.writeSignedInt(mSlot);
    stream.writeArray(mOption1, &Enchant::write);
    stream.writeArray(mOption2, &Enchant::write);
    stream.writeArray(mOption3, &Enchant::write);
}

Result<> ItemEnchants::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedInt(mSlot); !status) return status;
    if (auto status = stream.readArray(mOption1, &Enchant::read); !status) return status;
    if (auto status = stream.readArray(mOption2, &Enchant::read); !status) return status;
    return stream.readArray(mOption3, &Enchant::read);
}

void EnchantOption::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(mCost);
    mEnchants.write(stream);
    stream.writeString(mEnchantName);
    stream.writeUnsignedVarInt(mNetId);
}

Result<> EnchantOption::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt(mCost); !status) return status;
    if (auto status = mEnchants.read(stream); !status) return status;
    if (auto status = stream.readString(mEnchantName); !status) return status;
    return stream.readUnsignedVarInt(mNetId);
}

} // namespace sculk::protocol::inline abi_v944
