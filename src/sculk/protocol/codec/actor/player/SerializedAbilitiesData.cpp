// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/actor/player/SerializedAbilitiesData.hpp"

namespace sculk::protocol::inline abi_v944 {

void SerializedAbilitiesData::write(BinaryStream& stream) const {
    stream.writeSignedInt64(mPlayerRawId);
    stream.writeByte(mPlayerPermission);
    stream.writeByte(mCommandPermission);
    stream.writeArray(mLayers, [](BinaryStream& stream, const SerializedLayer& layer) {
        stream.writeUnsignedShort(layer.mLayer);
        stream.writeUnsignedInt(layer.mAbilitiesSet);
        stream.writeUnsignedInt(layer.mAbilitiesValue);
        stream.writeFloat(layer.mFlySpeed);
        stream.writeFloat(layer.mVerticalFlySpeed);
        stream.writeFloat(layer.mWalkSpeed);
    });
}

Result<> SerializedAbilitiesData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedInt64(mPlayerRawId); !status) return status;
    if (auto status = stream.readByte(mPlayerPermission); !status) return status;
    if (auto status = stream.readByte(mCommandPermission); !status) return status;
    if (auto status = stream.readArray(
            mLayers,
            [](ReadOnlyBinaryStream& stream, SerializedLayer& layer) {
                if (auto status = stream.readUnsignedShort(layer.mLayer); !status) return status;
                if (auto status = stream.readUnsignedInt(layer.mAbilitiesSet); !status) return status;
                if (auto status = stream.readUnsignedInt(layer.mAbilitiesValue); !status) return status;
                if (auto status = stream.readFloat(layer.mFlySpeed); !status) return status;
                if (auto status = stream.readFloat(layer.mVerticalFlySpeed); !status) return status;
                return stream.readFloat(layer.mWalkSpeed);
            }
        );
        !status) {
        return status;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
