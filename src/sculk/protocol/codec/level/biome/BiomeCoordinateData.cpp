// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeCoordinateData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BiomeCoordinateData::write(BinaryStream& stream) const {
    stream.writeVarInt(mMinValueType);
    stream.writeSignedShort(mMinValue);
    stream.writeVarInt(mMaxValueType);
    stream.writeSignedShort(mMaxValue);
    stream.writeUnsignedInt(mGridOffset);
    stream.writeUnsignedInt(mGridStepSize);
    stream.writeVarInt(mDistribution);
}

Result<> BiomeCoordinateData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mMinValueType); !status) return status;
    if (auto status = stream.readSignedShort(mMinValue); !status) return status;
    if (auto status = stream.readVarInt(mMaxValueType); !status) return status;
    if (auto status = stream.readSignedShort(mMaxValue); !status) return status;
    if (auto status = stream.readUnsignedInt(mGridOffset); !status) return status;
    if (auto status = stream.readUnsignedInt(mGridStepSize); !status) return status;
    return stream.readVarInt(mDistribution);
}

} // namespace sculk::protocol::inline abi_v944
