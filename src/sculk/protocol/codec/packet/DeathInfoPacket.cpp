// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/DeathInfoPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds DeathInfoPacket::getId() const noexcept { return MinecraftPacketIds::DeathInfo; }

std::string_view DeathInfoPacket::getName() const noexcept { return "DeathInfoPacket"; }

void DeathInfoPacket::write(BinaryStream& stream) const {
    stream.writeString(mDeathCauseAttackName);
    stream.writeArray(mDeathCauseMessageList, &BinaryStream::writeString);
}

Result<> DeathInfoPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mDeathCauseAttackName); !status) return status;
    return stream.readArray(mDeathCauseMessageList, &ReadOnlyBinaryStream::readString);
}

} // namespace sculk::protocol::inline abi_v944
