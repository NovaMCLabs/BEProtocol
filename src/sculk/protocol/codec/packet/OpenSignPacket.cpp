// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/OpenSignPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds OpenSignPacket::getId() const noexcept { return MinecraftPacketIds::OpenSign; }

std::string_view OpenSignPacket::getName() const noexcept { return "OpenSignPacket"; }

void OpenSignPacket::write(BinaryStream& stream) const {
    mPosition.write(stream);
    stream.writeBool(mIsFrontSide);
}

Result<> OpenSignPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mPosition.read(stream); !status) return status;
    return stream.readBool(mIsFrontSide);
}

} // namespace sculk::protocol::inline abi_v944
