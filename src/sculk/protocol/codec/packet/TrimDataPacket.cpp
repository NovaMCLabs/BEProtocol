// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/TrimDataPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void TrimDataPacket::TrimPattern::write(BinaryStream& stream) const {
    stream.writeString(mItemName);
    stream.writeString(mPatternId);
}

Result<> TrimDataPacket::TrimPattern::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mItemName); !status) return status;
    return stream.readString(mPatternId);
}

void TrimDataPacket::TrimMaterial::write(BinaryStream& stream) const {
    stream.writeString(mMaterialId);
    stream.writeString(mColor);
    stream.writeString(mItemName);
}

Result<> TrimDataPacket::TrimMaterial::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mMaterialId); !status) return status;
    if (auto status = stream.readString(mColor); !status) return status;
    return stream.readString(mItemName);
}

MinecraftPacketIds TrimDataPacket::getId() const noexcept { return MinecraftPacketIds::TrimData; }
std::string_view   TrimDataPacket::getName() const noexcept { return "TrimDataPacket"; }
void               TrimDataPacket::write(BinaryStream& stream) const {
    stream.writeArray(mTrimPatternList, &TrimPattern::write);
    stream.writeArray(mTrimMaterialList, &TrimMaterial::write);
}
Result<> TrimDataPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readArray(mTrimPatternList, &TrimPattern::read); !status) return status;
    return stream.readArray(mTrimMaterialList, &TrimMaterial::read);
}

} // namespace sculk::protocol::inline abi_v944
