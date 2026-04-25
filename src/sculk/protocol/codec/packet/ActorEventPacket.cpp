// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ActorEventPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ActorEventPacket::getId() const noexcept { return MinecraftPacketIds::ActorEvent; }

std::string_view ActorEventPacket::getName() const noexcept { return "ActorEventPacket"; }

void ActorEventPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mRuntimeId);
    stream.writeEnum(mEventId, &BinaryStream::writeByte);
    stream.writeVarInt(mData);
}

Result<> ActorEventPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mRuntimeId); !status) return status;
    if (auto status = stream.readEnum(mEventId, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readVarInt(mData);
}

} // namespace sculk::protocol::inline abi_v944
