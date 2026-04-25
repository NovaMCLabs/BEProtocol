// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeSurfaceMaterialData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BiomeSurfaceMaterialData::write(BinaryStream& stream) const {
    stream.writeSignedInt(mTopBlock);
    stream.writeSignedInt(mMidBlock);
    stream.writeSignedInt(mSeaFloorBlock);
    stream.writeSignedInt(mFoundationBlock);
    stream.writeSignedInt(mSeaBlock);
    stream.writeSignedInt(mSeaFloorDepth);
}

Result<> BiomeSurfaceMaterialData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedInt(mTopBlock); !status) return status;
    if (auto status = stream.readSignedInt(mMidBlock); !status) return status;
    if (auto status = stream.readSignedInt(mSeaFloorBlock); !status) return status;
    if (auto status = stream.readSignedInt(mFoundationBlock); !status) return status;
    if (auto status = stream.readSignedInt(mSeaBlock); !status) return status;
    return stream.readSignedInt(mSeaFloorDepth);
}

} // namespace sculk::protocol::inline abi_v944
