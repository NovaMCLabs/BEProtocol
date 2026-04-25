// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ActorPickRequestPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ActorPickRequestPacket::getId() const noexcept { return MinecraftPacketIds::ActorPickRequest; }

std::string_view ActorPickRequestPacket::getName() const noexcept { return "ActorPickRequestPacket"; }

void ActorPickRequestPacket::write(BinaryStream& stream) const {
    stream.writeSignedInt64(mActorId);
    stream.writeByte(mMaxSlots);
    stream.writeBool(mWithData);
}

Result<> ActorPickRequestPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedInt64(mActorId); !status) return status;
    if (auto status = stream.readByte(mMaxSlots); !status) return status;
    return stream.readBool(mWithData);
}

} // namespace sculk::protocol::inline abi_v944
