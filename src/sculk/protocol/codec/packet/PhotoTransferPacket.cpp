// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PhotoTransferPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds PhotoTransferPacket::getId() const noexcept { return MinecraftPacketIds::PhotoTransfer; }

std::string_view PhotoTransferPacket::getName() const noexcept { return "PhotoTransferPacket"; }

void PhotoTransferPacket::write(BinaryStream& stream) const {
    stream.writeString(mPhotoName);
    stream.writeString(mPhotoData);
    stream.writeString(mBookId);
    stream.writeEnum(mType, &BinaryStream::writeByte);
    stream.writeEnum(mSourceType, &BinaryStream::writeByte);
    stream.writeSignedInt64(mOwnerId);
    stream.writeString(mNewPhotoName);
}

Result<> PhotoTransferPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mPhotoName));
    _SCULK_READ(stream.readString(mPhotoData));
    _SCULK_READ(stream.readString(mBookId));
    _SCULK_READ(stream.readEnum(mType, &ReadOnlyBinaryStream::readByte));
    _SCULK_READ(stream.readEnum(mSourceType, &ReadOnlyBinaryStream::readByte));
    _SCULK_READ(stream.readSignedInt64(mOwnerId));
    return stream.readString(mNewPhotoName);
}

} // namespace sculk::protocol::inline abi_v975
