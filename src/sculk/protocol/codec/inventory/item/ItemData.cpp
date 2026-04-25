// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/item/ItemData.hpp"

namespace sculk::protocol::inline abi_v944 {

void ItemData::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeSignedShort(mId);
    stream.writeBool(mIsComponentBased);
    stream.writeEnum(mVersion, &BinaryStream::writeVarInt);
    mComponentData.write(stream);
}

Result<> ItemData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readSignedShort(mId); !status) return status;
    if (auto status = stream.readBool(mIsComponentBased); !status) return status;
    if (auto status = stream.readEnum(mVersion, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    return mComponentData.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
