// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeWeightedTemperatureData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BiomeWeightedTemperatureData::write(BinaryStream& stream) const {
    stream.writeVarInt(mTemperature);
    stream.writeUnsignedInt(mWeight);
}

Result<> BiomeWeightedTemperatureData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mTemperature); !status) return status;
    return stream.readUnsignedInt(mWeight);
}

} // namespace sculk::protocol::inline abi_v944
