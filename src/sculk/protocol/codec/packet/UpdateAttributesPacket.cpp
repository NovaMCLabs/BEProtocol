// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateAttributesPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UpdateAttributesPacket::getId() const noexcept { return MinecraftPacketIds::UpdateAttributes; }
std::string_view   UpdateAttributesPacket::getName() const noexcept { return "UpdateAttributesPacket"; }

void UpdateAttributesPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeArray(mAttributes, &Attribute::write);
    stream.writeUnsignedVarInt64(mTick);
}

Result<> UpdateAttributesPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    if (auto status = stream.readArray(mAttributes, &Attribute::read); !status) return status;
    return stream.readUnsignedVarInt64(mTick);
}

} // namespace sculk::protocol::inline abi_v944
