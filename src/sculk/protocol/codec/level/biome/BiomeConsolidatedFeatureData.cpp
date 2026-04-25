// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeConsolidatedFeatureData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BiomeConsolidatedFeatureData::write(BinaryStream& stream) const {
    mScatter.write(stream);
    stream.writeSignedShort(mFeature);
    stream.writeSignedShort(mIdentifier);
    stream.writeSignedShort(mPass);
    stream.writeBool(mCanUseInternal);
}

Result<> BiomeConsolidatedFeatureData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mScatter.read(stream); !status) return status;
    if (auto status = stream.readSignedShort(mFeature); !status) return status;
    if (auto status = stream.readSignedShort(mIdentifier); !status) return status;
    if (auto status = stream.readSignedShort(mPass); !status) return status;
    return stream.readBool(mCanUseInternal);
}

} // namespace sculk::protocol::inline abi_v944
