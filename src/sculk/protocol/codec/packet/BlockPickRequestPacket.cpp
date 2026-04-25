// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/BlockPickRequestPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds BlockPickRequestPacket::getId() const noexcept { return MinecraftPacketIds::BlockPickRequest; }

std::string_view BlockPickRequestPacket::getName() const noexcept { return "BlockPickRequestPacket"; }

void BlockPickRequestPacket::write(BinaryStream& stream) const {
    mPosition.write(stream);
    stream.writeBool(mWithData);
    stream.writeByte(mMaxSlots);
}

Result<> BlockPickRequestPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = stream.readBool(mWithData); !status) return status;
    return stream.readByte(mMaxSlots);
}

} // namespace sculk::protocol::inline abi_v944
