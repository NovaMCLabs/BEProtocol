// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/EmoteListPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds EmoteListPacket::getId() const noexcept { return MinecraftPacketIds::EmoteList; }

std::string_view EmoteListPacket::getName() const noexcept { return "EmoteListPacket"; }

void EmoteListPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeArray(mEmotePieceIds, &UUID::write);
}

Result<> EmoteListPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    return stream.readArray(mEmotePieceIds, &UUID::read);
}

} // namespace sculk::protocol::inline abi_v944
