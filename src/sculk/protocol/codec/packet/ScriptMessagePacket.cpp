// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ScriptMessagePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ScriptMessagePacket::getId() const noexcept { return MinecraftPacketIds::ScriptMessage; }

std::string_view ScriptMessagePacket::getName() const noexcept { return "ScriptMessagePacket"; }

void ScriptMessagePacket::write(BinaryStream& stream) const {
    stream.writeString(mMessageId);
    stream.writeString(mMessageValue);
}

Result<> ScriptMessagePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mMessageId); !status) return status;
    return stream.readString(mMessageValue);
}

} // namespace sculk::protocol::inline abi_v944
