// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/DisconnectPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds DisconnectPacket::getId() const noexcept { return MinecraftPacketIds::Disconnect; }

std::string_view DisconnectPacket::getName() const noexcept { return "DisconnectPacket"; }

void DisconnectPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mReason, &BinaryStream::writeVarInt);
    stream.writeBool(mSkipMessage);
    if (!mSkipMessage) {
        stream.writeString(mMessage);
        stream.writeString(mFilteredMessage);
    }
}

Result<> DisconnectPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mReason, &ReadOnlyBinaryStream::readVarInt); !status) return status;
    if (auto status = stream.readBool(mSkipMessage); !status) return status;
    if (!mSkipMessage) {
        if (auto status = stream.readString(mMessage); !status) return status;
        if (auto status = stream.readString(mFilteredMessage); !status) return status;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
