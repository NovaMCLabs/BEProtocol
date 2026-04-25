// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PartyChangedPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PartyChangedPacket::getId() const noexcept { return MinecraftPacketIds::PartyChanged; }

std::string_view PartyChangedPacket::getName() const noexcept { return "PartyChangedPacket"; }

void PartyChangedPacket::write(BinaryStream& stream) const { stream.writeString(mPartyId); }

Result<> PartyChangedPacket::read(ReadOnlyBinaryStream& stream) { return stream.readString(mPartyId); }

} // namespace sculk::protocol::inline abi_v944
