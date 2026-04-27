// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SpawnExperienceOrbPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SpawnExperienceOrbPacket::getId() const noexcept { return MinecraftPacketIds::SpawnExperienceOrb; }

std::string_view SpawnExperienceOrbPacket::getName() const noexcept { return "SpawnExperienceOrbPacket"; }

void SpawnExperienceOrbPacket::write(BinaryStream& stream) const {
    mPosition.write(stream);
    stream.writeVarInt(mXpValue);
}

Result<> SpawnExperienceOrbPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(mPosition.read(stream));
    return stream.readVarInt(mXpValue);
}

} // namespace sculk::protocol::inline abi_v975
