// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SubClientLoginPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SubClientLoginPacket::getId() const noexcept { return MinecraftPacketIds::SubClientLogin; }

std::string_view SubClientLoginPacket::getName() const noexcept { return "SubClientLoginPacket"; }

void SubClientLoginPacket::write(BinaryStream& stream) const { mConnectionRequest.write(stream); }

Result<> SubClientLoginPacket::read(ReadOnlyBinaryStream& stream) { return mConnectionRequest.read(stream); }

} // namespace sculk::protocol::inline abi_v975
