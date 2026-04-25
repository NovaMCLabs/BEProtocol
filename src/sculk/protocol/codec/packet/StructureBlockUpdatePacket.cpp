// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/StructureBlockUpdatePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds StructureBlockUpdatePacket::getId() const noexcept {
    return MinecraftPacketIds::StructureBlockUpdate;
}

std::string_view StructureBlockUpdatePacket::getName() const noexcept { return "StructureBlockUpdatePacket"; }

void StructureBlockUpdatePacket::write(BinaryStream& stream) const {
    mBlockPosition.write(stream);
    mStructureData.write(stream);
    stream.writeBool(mTrigger);
    stream.writeBool(mIsWaterLogged);
}

Result<> StructureBlockUpdatePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mBlockPosition.read(stream); !status) return status;
    if (auto status = mStructureData.read(stream); !status) return status;
    if (auto status = stream.readBool(mTrigger); !status) return status;
    return stream.readBool(mIsWaterLogged);
}

} // namespace sculk::protocol::inline abi_v944
