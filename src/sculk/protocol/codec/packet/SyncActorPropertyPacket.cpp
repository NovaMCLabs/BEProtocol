// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SyncActorPropertyPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds SyncActorPropertyPacket::getId() const noexcept { return MinecraftPacketIds::SyncActorProperty; }

std::string_view SyncActorPropertyPacket::getName() const noexcept { return "SyncActorPropertyPacket"; }

void SyncActorPropertyPacket::write(BinaryStream& stream) const { mPropertyData.write(stream); }

Result<> SyncActorPropertyPacket::read(ReadOnlyBinaryStream& stream) { return mPropertyData.read(stream); }

} // namespace sculk::protocol::inline abi_v975
