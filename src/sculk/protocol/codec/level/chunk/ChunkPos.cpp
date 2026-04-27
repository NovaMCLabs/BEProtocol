// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/chunk/ChunkPos.hpp"

namespace sculk::protocol::inline abi_v975 {

void ChunkPos::write(BinaryStream& stream) const {
    stream.writeVarInt(mX);
    stream.writeVarInt(mZ);
}

Result<> ChunkPos::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readVarInt(mX));
    return stream.readVarInt(mZ);
}

} // namespace sculk::protocol::inline abi_v975
