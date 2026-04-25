// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CodeBuilderPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds CodeBuilderPacket::getId() const noexcept { return MinecraftPacketIds::CodeBuilder; }

std::string_view CodeBuilderPacket::getName() const noexcept { return "CodeBuilderPacket"; }

void CodeBuilderPacket::write(BinaryStream& stream) const {
    stream.writeString(mUrl);
    stream.writeBool(mShouldOpen);
}

Result<> CodeBuilderPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mUrl); !status) return status;
    return stream.readBool(mShouldOpen);
}

} // namespace sculk::protocol::inline abi_v944
