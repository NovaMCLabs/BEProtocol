// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeTagsData.hpp"

namespace sculk::protocol::inline abi_v975 {

void BiomeTagsData::write(BinaryStream& stream) const { stream.writeArray(mTags, &BinaryStream::writeSignedShort); }

Result<> BiomeTagsData::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mTags, &ReadOnlyBinaryStream::readSignedShort);
}

} // namespace sculk::protocol::inline abi_v975
