// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ChangeDimensionPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ChangeDimensionPacket::getId() const noexcept { return MinecraftPacketIds::ChangeDimension; }

std::string_view ChangeDimensionPacket::getName() const noexcept { return "ChangeDimensionPacket"; }

void ChangeDimensionPacket::write(BinaryStream& stream) const {
    stream.writeVarInt(mDimensionType);
    mPosition.write(stream);
    stream.writeBool(mRespawn);
    stream.writeOptional(mLoadingScreenId, &BinaryStream::writeUnsignedInt);
}

Result<> ChangeDimensionPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mDimensionType); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = stream.readBool(mRespawn); !status) return status;
    return stream.readOptional(mLoadingScreenId, &ReadOnlyBinaryStream::readUnsignedInt);
}

} // namespace sculk::protocol::inline abi_v944
