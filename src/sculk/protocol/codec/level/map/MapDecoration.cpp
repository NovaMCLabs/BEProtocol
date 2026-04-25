// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/map/MapDecoration.hpp"

namespace sculk::protocol::inline abi_v944 {

void MapDecoration::write(BinaryStream& stream) const {
    stream.writeByte(mType);
    stream.writeByte(mRotation);
    stream.writeByte(mX);
    stream.writeByte(mY);
    stream.writeString(mLabel);
    stream.writeUnsignedVarInt(mColor);
}

Result<> MapDecoration::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readByte(mType); !status) return status;
    if (auto status = stream.readByte(mRotation); !status) return status;
    if (auto status = stream.readByte(mX); !status) return status;
    if (auto status = stream.readByte(mY); !status) return status;
    if (auto status = stream.readString(mLabel); !status) return status;
    return stream.readUnsignedVarInt(mColor);
}

} // namespace sculk::protocol::inline abi_v944
