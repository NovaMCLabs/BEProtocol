// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/LevelSoundEventPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds LevelSoundEventPacket::getId() const noexcept { return MinecraftPacketIds::LevelSoundEvent; }

std::string_view LevelSoundEventPacket::getName() const noexcept { return "LevelSoundEventPacket"; }

void LevelSoundEventPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(mEventId);
    mPosition.write(stream);
    stream.writeVarInt(mData);
    stream.writeString(mActorIdentifier);
    stream.writeBool(mIsBabyMob);
    stream.writeBool(mIsGlobal);
    stream.writeSignedInt64(mActorUniqueId);
}

Result<> LevelSoundEventPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt(mEventId); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = stream.readVarInt(mData); !status) return status;
    if (auto status = stream.readString(mActorIdentifier); !status) return status;
    if (auto status = stream.readBool(mIsBabyMob); !status) return status;
    if (auto status = stream.readBool(mIsGlobal); !status) return status;
    return stream.readSignedInt64(mActorUniqueId);
}

} // namespace sculk::protocol::inline abi_v944
