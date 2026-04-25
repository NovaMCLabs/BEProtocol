// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/DebugDrawerPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds DebugDrawerPacket::getId() const noexcept { return MinecraftPacketIds::DebugDrawer; }

std::string_view DebugDrawerPacket::getName() const noexcept { return "DebugDrawerPacket"; }

void DebugDrawerPacket::write(BinaryStream& stream) const { stream.writeArray(mShapes, &DebugShape::write); }

Result<> DebugDrawerPacket::read(ReadOnlyBinaryStream& stream) { return stream.readArray(mShapes, &DebugShape::read); }

} // namespace sculk::protocol::inline abi_v944
