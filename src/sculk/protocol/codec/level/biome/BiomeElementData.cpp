// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeElementData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BiomeElementData::write(BinaryStream& stream) const {
    stream.writeFloat(mNoiseFrequencyScale);
    stream.writeFloat(mNoiseLowerBound);
    stream.writeFloat(mNoiseUpperBound);
    stream.writeVarInt(mHeightMinType);
    stream.writeSignedShort(mHeightMin);
    stream.writeVarInt(mHeightMaxType);
    stream.writeSignedShort(mHeightMax);
    mAdjustedMaterials.write(stream);
}

Result<> BiomeElementData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mNoiseFrequencyScale); !status) return status;
    if (auto status = stream.readFloat(mNoiseLowerBound); !status) return status;
    if (auto status = stream.readFloat(mNoiseUpperBound); !status) return status;
    if (auto status = stream.readVarInt(mHeightMinType); !status) return status;
    if (auto status = stream.readSignedShort(mHeightMin); !status) return status;
    if (auto status = stream.readVarInt(mHeightMaxType); !status) return status;
    if (auto status = stream.readSignedShort(mHeightMax); !status) return status;
    return mAdjustedMaterials.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
