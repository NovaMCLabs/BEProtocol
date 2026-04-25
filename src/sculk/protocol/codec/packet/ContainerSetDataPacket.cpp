// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ContainerSetDataPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ContainerSetDataPacket::getId() const noexcept { return MinecraftPacketIds::ContainerSetData; }
std::string_view   ContainerSetDataPacket::getName() const noexcept { return "ContainerSetDataPacket"; }

void ContainerSetDataPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mContainerId, &BinaryStream::writeByte);
    stream.writeVarInt(mId);
    stream.writeVarInt(mValue);
}

Result<> ContainerSetDataPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mContainerId, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = stream.readVarInt(mId); !status) return status;
    return stream.readVarInt(mValue);
}

} // namespace sculk::protocol::inline abi_v944
