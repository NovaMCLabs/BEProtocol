// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeDefinitionChunkGenData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BiomeDefinitionChunkGenData::write(BinaryStream& stream) const {
    stream.writeOptional(mClimate, &BiomeClimateData::write);
    stream.writeOptional(mConsolidatedFeatures, &BiomeConsolidatedFeaturesData::write);
    stream.writeOptional(mMountainParams, &BiomeMountainParamsData::write);
    stream.writeOptional(mSurfaceMaterialAdjustments, &BiomeSurfaceMaterialAdjustmentData::write);
    stream.writeOptional(mSurfaceMaterials, &BiomeSurfaceMaterialData::write);
    stream.writeBool(mHasDefaultOverworldSurface);
    stream.writeBool(mHasSwampSurface);
    stream.writeBool(mHasFrozenOceanSurface);
    stream.writeBool(mHasTheEndSurface);
    stream.writeOptional(mMesaSurface, &BiomeMesaSurfaceData::write);
    stream.writeOptional(mCappedSurface, &BiomeCappedSurfaceData::write);
    stream.writeOptional(mOverworldGenRules, &BiomeOverworldGenRulesData::write);
    stream.writeOptional(mMultinoiseGenRules, &BiomeMultinoiseGenRulesData::write);
    stream.writeOptional(mLegacyWorldGenRules, &BiomeLegacyWorldGenRulesData::write);
    stream.writeOptional(mBiomeReplacementData, &BiomeReplacementData::write);
    stream.writeOptional(mVillageType, &BinaryStream::writeByte);
}

Result<> BiomeDefinitionChunkGenData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readOptional(mClimate, &BiomeClimateData::read); !status) return status;
    if (auto status = stream.readOptional(mConsolidatedFeatures, &BiomeConsolidatedFeaturesData::read); !status)
        return status;
    if (auto status = stream.readOptional(mMountainParams, &BiomeMountainParamsData::read); !status) return status;
    if (auto status = stream.readOptional(mSurfaceMaterialAdjustments, &BiomeSurfaceMaterialAdjustmentData::read);
        !status)
        return status;
    if (auto status = stream.readOptional(mSurfaceMaterials, &BiomeSurfaceMaterialData::read); !status) return status;
    if (auto status = stream.readBool(mHasDefaultOverworldSurface); !status) return status;
    if (auto status = stream.readBool(mHasSwampSurface); !status) return status;
    if (auto status = stream.readBool(mHasFrozenOceanSurface); !status) return status;
    if (auto status = stream.readBool(mHasTheEndSurface); !status) return status;
    if (auto status = stream.readOptional(mMesaSurface, &BiomeMesaSurfaceData::read); !status) return status;
    if (auto status = stream.readOptional(mCappedSurface, &BiomeCappedSurfaceData::read); !status) return status;
    if (auto status = stream.readOptional(mOverworldGenRules, &BiomeOverworldGenRulesData::read); !status)
        return status;
    if (auto status = stream.readOptional(mMultinoiseGenRules, &BiomeMultinoiseGenRulesData::read); !status)
        return status;
    if (auto status = stream.readOptional(mLegacyWorldGenRules, &BiomeLegacyWorldGenRulesData::read); !status)
        return status;
    if (auto status = stream.readOptional(mBiomeReplacementData, &BiomeReplacementData::read); !status) return status;
    return stream.readOptional(mVillageType, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944