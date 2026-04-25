// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeScatterParamData.hpp"

namespace sculk::protocol::inline abi_v944 {

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
    if (auto status = stream.readArray(mCoordinate, &BiomeCoordinateData::read); !status) return status;
    if (auto status = stream.readVarInt(mEvalOrder); !status) return status;
    if (auto status = stream.readVarInt(mChancePercentType); !status) return status;
    if (auto status = stream.readSignedShort(mChancePercent); !status) return status;
    if (auto status = stream.readSignedInt(mChanceNumeartor); !status) return status;
    if (auto status = stream.readSignedInt(mChanceDenominator); !status) return status;
    if (auto status = stream.readVarInt(mIterationsType); !status) return status;
    return stream.readSignedShort(mIterations);
}

} // namespace sculk::protocol::inline abi_v944
