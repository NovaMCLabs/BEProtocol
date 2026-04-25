// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/LoginPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds LoginPacket::getId() const noexcept { return MinecraftPacketIds::Login; }

std::string_view LoginPacket::getName() const noexcept { return "LoginPacket"; }

void LoginPacket::write(BinaryStream& stream) const {
    stream.writeSignedBigEndianInt(mNetworkVersion);
    mConnectionRequest.write(stream);
}

Result<> LoginPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readSignedBigEndianInt(mNetworkVersion));
    return mConnectionRequest.read(stream);
}

} // namespace sculk::protocol::inline abi_v975
