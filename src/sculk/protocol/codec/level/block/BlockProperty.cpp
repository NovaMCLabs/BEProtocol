// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/block/BlockProperty.hpp"
#include "sculk/protocol/codec/nbt/TagVariant.hpp"

namespace sculk::protocol::inline abi_v944 {

void BlockProperty::write(BinaryStream& stream) const {
    stream.writeString(mName);
    mNbt.write(stream);
}

Result<> BlockProperty::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    return mNbt.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
