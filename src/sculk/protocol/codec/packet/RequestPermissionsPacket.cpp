// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/RequestPermissionsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds RequestPermissionsPacket::getId() const noexcept { return MinecraftPacketIds::RequestPermissions; }

std::string_view RequestPermissionsPacket::getName() const noexcept { return "RequestPermissionsPacket"; }

void RequestPermissionsPacket::write(BinaryStream& stream) const {
    stream.writeSignedInt64(mPlayerRawId);
    stream.writeVarInt(mPermissionLevel);
    stream.writeUnsignedShort(mCustomPermissionFlag);
}

Result<> RequestPermissionsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedInt64(mPlayerRawId); !status) return status;
    if (auto status = stream.readVarInt(mPermissionLevel); !status) return status;
    return stream.readUnsignedShort(mCustomPermissionFlag);
}

} // namespace sculk::protocol::inline abi_v944
