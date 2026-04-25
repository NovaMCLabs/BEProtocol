// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/item/NetworkItemStackDescriptor.hpp"

namespace sculk::protocol::inline abi_v944 {

void NetworkItemStackDescriptor::write(BinaryStream& stream) const {
    if (mId == 0) {
        stream.writeVarInt(0);
    } else {
        stream.writeVarInt(mId);
        stream.writeUnsignedShort(mStackSize);
        stream.writeUnsignedVarInt(mAux);
        stream.writeOptional(mNetId, &BinaryStream::writeVarInt);
        stream.writeVarInt(mBlockRuntimeId);
        stream.writeString(mUserData);
    }
}

[[nodiscard]] Result<> NetworkItemStackDescriptor::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mId); !status) return status;
    if (mId == 0) {
        return {}; // Empty item stack
    } else {
        if (auto status = stream.readUnsignedShort(mStackSize); !status) return status;
        if (auto status = stream.readUnsignedVarInt(mAux); !status) return status;
        if (auto status = stream.readOptional(mNetId, &ReadOnlyBinaryStream::readVarInt); !status) return status;
        if (auto status = stream.readVarInt(mBlockRuntimeId); !status) return status;
        return stream.readString(mUserData);
    }
}

} // namespace sculk::protocol::inline abi_v944
