// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/actor/SyncedAttribute.hpp"

namespace sculk::protocol::inline abi_v944 {

void SyncedAttribute::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeFloat(mMinValue);
    stream.writeFloat(mMaxValue);
    stream.writeFloat(mCurrentValue);
}

Result<> SyncedAttribute::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readFloat(mMinValue); !status) return status;
    if (auto status = stream.readFloat(mMaxValue); !status) return status;
    return stream.readFloat(mCurrentValue);
}

} // namespace sculk::protocol::inline abi_v944
