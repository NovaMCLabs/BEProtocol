// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/NpcDialoguePacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds NpcDialoguePacket::getId() const noexcept { return MinecraftPacketIds::NpcDialogue; }

std::string_view NpcDialoguePacket::getName() const noexcept { return "NpcDialoguePacket"; }

void NpcDialoguePacket::write(BinaryStream& stream) const {
    stream.writeUnsignedInt64(mNpcId);
    stream.writeEnum(mActionType, &BinaryStream::writeVarInt);
    stream.writeString(mDialogue);
    stream.writeString(mSceneName);
    stream.writeString(mNpcName);
    stream.writeString(mActionJSON);
}

Result<> NpcDialoguePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedInt64(mNpcId));
    _SCULK_READ(stream.readEnum(mActionType, &ReadOnlyBinaryStream::readVarInt));
    _SCULK_READ(stream.readString(mDialogue));
    _SCULK_READ(stream.readString(mSceneName));
    _SCULK_READ(stream.readString(mNpcName));
    return stream.readString(mActionJSON);
}

} // namespace sculk::protocol::inline abi_v975
