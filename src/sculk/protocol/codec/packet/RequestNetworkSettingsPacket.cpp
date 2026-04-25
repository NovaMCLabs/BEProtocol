// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/RequestNetworkSettingsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds RequestNetworkSettingsPacket::getId() const noexcept {
    return MinecraftPacketIds::RequestNetworkSettings;
}

std::string_view RequestNetworkSettingsPacket::getName() const noexcept { return "RequestNetworkSettingsPacket"; }

void RequestNetworkSettingsPacket::write(BinaryStream& stream) const {
    stream.writeSignedBigEndianInt(mClientNetworkVersion);
}

Result<> RequestNetworkSettingsPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readSignedBigEndianInt(mClientNetworkVersion);
}

} // namespace sculk::protocol::inline abi_v944
