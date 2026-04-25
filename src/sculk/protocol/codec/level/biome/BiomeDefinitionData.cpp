// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeDefinitionData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BiomeDefinitionData::write(BinaryStream& stream) const {
    stream.writeSignedShort(mBiomeId);
    stream.writeFloat(mTemperature);
    stream.writeFloat(mDownfall);
    stream.writeFloat(mFoliageSnow);
    stream.writeFloat(mDepth);
    stream.writeFloat(mScale);
    stream.writeSignedInt(mMapWaterColorARGB);
    stream.writeBool(mRain);
    stream.writeOptional(mTags, &BiomeTagsData::write);
    stream.writeOptional(mChunkGenData, &BiomeDefinitionChunkGenData::write);
}

Result<> BiomeDefinitionData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedShort(mBiomeId); !status) return status;
    if (auto status = stream.readFloat(mTemperature); !status) return status;
    if (auto status = stream.readFloat(mDownfall); !status) return status;
    if (auto status = stream.readFloat(mFoliageSnow); !status) return status;
    if (auto status = stream.readFloat(mDepth); !status) return status;
    if (auto status = stream.readFloat(mScale); !status) return status;
    if (auto status = stream.readSignedInt(mMapWaterColorARGB); !status) return status;
    if (auto status = stream.readBool(mRain); !status) return status;
    if (auto status = stream.readOptional(mTags, &BiomeTagsData::read); !status) return status;
    return stream.readOptional(mChunkGenData, &BiomeDefinitionChunkGenData::read);
}

} // namespace sculk::protocol::inline abi_v944