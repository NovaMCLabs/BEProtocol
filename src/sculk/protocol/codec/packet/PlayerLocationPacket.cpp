// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlayerLocationPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PlayerLocationPacket::getId() const noexcept { return MinecraftPacketIds::PlayerLocation; }

std::string_view PlayerLocationPacket::getName() const noexcept { return "PlayerLocationPacket"; }

void PlayerLocationPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeSignedInt);
    stream.writeVarInt64(mActorUniqueId);
    if (mType == Type::PlayerLocationCoordinates) {
        mPosition.write(stream);
    }
}

Result<> PlayerLocationPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readSignedInt); !status) return status;
    if (auto status = stream.readVarInt64(mActorUniqueId); !status) return status;
    if (mType == Type::PlayerLocationCoordinates) {
        return mPosition.read(stream);
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
