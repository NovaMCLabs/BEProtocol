// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PacketViolationWarningPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PacketViolationWarningPacket::getId() const noexcept {
    return MinecraftPacketIds::PacketViolationWarning;
}

std::string_view PacketViolationWarningPacket::getName() const noexcept { return "PacketViolationWarningPacket"; }

void PacketViolationWarningPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeVarInt);
    stream.writeEnum(mSeverity, &BinaryStream::writeVarInt);
    stream.writeEnum(mPacketId, &BinaryStream::writeVarInt);
    stream.writeString(mContext);
}

Result<> PacketViolationWarningPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readEnum(mSeverity, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readEnum(mPacketId, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    return stream.readString(mContext);
}

} // namespace sculk::protocol::inline abi_v944
