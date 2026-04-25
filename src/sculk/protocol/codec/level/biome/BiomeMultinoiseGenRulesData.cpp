// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeMultinoiseGenRulesData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BiomeMultinoiseGenRulesData::write(BinaryStream& stream) const {
    stream.writeFloat(mTemperature);
    stream.writeFloat(mHumidity);
    stream.writeFloat(mAltitude);
    stream.writeFloat(mWeirdness);
    stream.writeFloat(mWeight);
}
Result<> BiomeMultinoiseGenRulesData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mTemperature); !status) return status;
    if (auto status = stream.readFloat(mHumidity); !status) return status;
    if (auto status = stream.readFloat(mAltitude); !status) return status;
    if (auto status = stream.readFloat(mWeirdness); !status) return status;
    return stream.readFloat(mWeight);
}

} // namespace sculk::protocol::inline abi_v944
