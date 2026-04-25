// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/actor/PropertySyncData.hpp"

namespace sculk::protocol::inline abi_v944 {

void PropertySyncData::write(BinaryStream& stream) const {
    stream.writeArray(mIntEntries, [&](const PropertySyncIntEntry& entry) {
        stream.writeUnsignedVarInt(entry.mPropertyIndex);
        stream.writeVarInt(entry.mData);
    });
    stream.writeArray(mFloatEntries, [&](const PropertySyncFloatEntry& entry) {
        stream.writeUnsignedVarInt(entry.mPropertyIndex);
        stream.writeFloat(entry.mData);
    });
}

Result<> PropertySyncData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readArray(
            mIntEntries,
            [&](PropertySyncIntEntry& entry) {
                if (auto status = stream.readUnsignedVarInt(entry.mPropertyIndex); !status) return status;
                if (auto status = stream.readVarInt(entry.mData); !status) return status;
                return Result<>{};
            }
        );
        !status) {
        return status;
    }
    return stream.readArray(mFloatEntries, [&](PropertySyncFloatEntry& entry) {
        if (auto status = stream.readUnsignedVarInt(entry.mPropertyIndex); !status) return status;
        return stream.readFloat(entry.mData);
    });
}

} // namespace sculk::protocol::inline abi_v944
