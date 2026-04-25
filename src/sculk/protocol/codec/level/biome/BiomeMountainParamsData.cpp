// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeMountainParamsData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BiomeMountainParamsData::write(BinaryStream& stream) const {
    stream.writeSignedInt(mSteepBlock);
    stream.writeBool(mNorthSlopes);
    stream.writeBool(mSouthSlopes);
    stream.writeBool(mWestSlopes);
    stream.writeBool(mEastSlopes);
    stream.writeBool(mTopSlideEnabled);
}

Result<> BiomeMountainParamsData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedInt(mSteepBlock); !status) return status;
    if (auto status = stream.readBool(mNorthSlopes); !status) return status;
    if (auto status = stream.readBool(mSouthSlopes); !status) return status;
    if (auto status = stream.readBool(mWestSlopes); !status) return status;
    if (auto status = stream.readBool(mEastSlopes); !status) return status;
    return stream.readBool(mTopSlideEnabled);
}

} // namespace sculk::protocol::inline abi_v944
