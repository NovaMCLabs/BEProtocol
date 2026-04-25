// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/TransferPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds TransferPacket::getId() const noexcept { return MinecraftPacketIds::Transfer; }

std::string_view TransferPacket::getName() const noexcept { return "TransferPacket"; }

void TransferPacket::write(BinaryStream& stream) const {
    stream.writeString(mServerAddress);
    stream.writeUnsignedShort(mServerPort);
    stream.writeBool(mReloadWorld);
}

Result<> TransferPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mServerAddress); !status) return status;
    if (auto status = stream.readUnsignedShort(mServerPort); !status) return status;
    return stream.readBool(mReloadWorld);
}

} // namespace sculk::protocol::inline abi_v944
