// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeScatterParamData.hpp"

namespace sculk::protocol::inline abi_v975 {

void BiomeScatterParamData::write(BinaryStream& stream) const {
    stream.writeArray(mCoordinate, &BiomeCoordinateData::write);
    stream.writeVarInt(mEvalOrder);
    stream.writeVarInt(mChancePercentType);
    stream.writeSignedShort(mChancePercent);
    stream.writeSignedInt(mChanceNumeartor);
    stream.writeSignedInt(mChanceDenominator);
    stream.writeVarInt(mIterationsType);
    stream.writeSignedShort(mIterations);
}

Result<> BiomeScatterParamData::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readArray(mCoordinate, &BiomeCoordinateData::read));
    _SCULK_READ(stream.readVarInt(mEvalOrder));
    _SCULK_READ(stream.readVarInt(mChancePercentType));
    _SCULK_READ(stream.readSignedShort(mChancePercent));
    _SCULK_READ(stream.readSignedInt(mChanceNumeartor));
    _SCULK_READ(stream.readSignedInt(mChanceDenominator));
    _SCULK_READ(stream.readVarInt(mIterationsType));
    return stream.readSignedShort(mIterations);
}

} // namespace sculk::protocol::inline abi_v975
