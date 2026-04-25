// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeClimateData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BiomeClimateData::write(BinaryStream& stream) const {
    stream.writeFloat(mTemperature);
    stream.writeFloat(mDownfall);
    stream.writeFloat(mSnowAccumulationMin);
    stream.writeFloat(mSnowAccumulationMax);
}

Result<> BiomeClimateData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mTemperature); !status) return status;
    if (auto status = stream.readFloat(mDownfall); !status) return status;
    if (auto status = stream.readFloat(mSnowAccumulationMin); !status) return status;
    return stream.readFloat(mSnowAccumulationMax);
}

} // namespace sculk::protocol::inline abi_v944
