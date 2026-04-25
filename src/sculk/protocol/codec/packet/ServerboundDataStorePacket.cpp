// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ServerboundDataStorePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ServerboundDataStorePacket::getId() const noexcept {
    return MinecraftPacketIds::ServerboundDataStore;
}

std::string_view ServerboundDataStorePacket::getName() const noexcept { return "ServerboundDataStorePacket"; }

void ServerboundDataStorePacket::write(BinaryStream& stream) const { mDataStoreUpdate.write(stream); }

Result<> ServerboundDataStorePacket::read(ReadOnlyBinaryStream& stream) { return mDataStoreUpdate.read(stream); }

} // namespace sculk::protocol::inline abi_v944
