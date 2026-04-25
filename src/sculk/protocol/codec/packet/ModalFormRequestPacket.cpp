// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ModalFormRequestPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ModalFormRequestPacket::getId() const noexcept { return MinecraftPacketIds::ModalFormRequest; }

std::string_view ModalFormRequestPacket::getName() const noexcept { return "ModalFormRequestPacket"; }

void ModalFormRequestPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(mFormId);
    stream.writeString(mFormJson);
}

Result<> ModalFormRequestPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt(mFormId); !status) return status;
    return stream.readString(mFormJson);
}

} // namespace sculk::protocol::inline abi_v944
