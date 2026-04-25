// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/LocatorBarPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds LocatorBarPacket::getId() const noexcept { return MinecraftPacketIds::LocatorBar; }

std::string_view LocatorBarPacket::getName() const noexcept { return "LocatorBarPacket"; }

void LocatorBarPacket::write(BinaryStream& stream) const {
    stream.writeArray(mWaypoints, &LocatorBarWaypointPayload::write);
}

Result<> LocatorBarPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mWaypoints, &LocatorBarWaypointPayload::read);
}

} // namespace sculk::protocol::inline abi_v944
