// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateClientOptionsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UpdateClientOptionsPacket::getId() const noexcept { return MinecraftPacketIds::UpdateClientOptions; }

std::string_view UpdateClientOptionsPacket::getName() const noexcept { return "UpdateClientOptionsPacket"; }

void UpdateClientOptionsPacket::write(BinaryStream& stream) const {
    stream.writeOptional(mUpdate.mGraphicsMode, [&](GraphicsMode mode) {
        stream.writeEnum(mode, &BinaryStream::writeByte);
    });
}

Result<> UpdateClientOptionsPacket::read(ReadOnlyBinaryStream& stream) {
    return stream.readOptional(mUpdate.mGraphicsMode, [&](GraphicsMode& mode) {
        return stream.readEnum(mode, &ReadOnlyBinaryStream::readByte);
    });
}

} // namespace sculk::protocol::inline abi_v944
