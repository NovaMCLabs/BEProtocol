// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientboundDataDrivenUIShowScreenPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ClientboundDataDrivenUIShowScreenPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientboundDataDrivenUIShowScreen;
}

std::string_view ClientboundDataDrivenUIShowScreenPacket::getName() const noexcept {
    return "ClientboundDataDrivenUIShowScreenPacket";
}

void ClientboundDataDrivenUIShowScreenPacket::write(BinaryStream& stream) const {
    stream.writeString(mScreenId);
    stream.writeUnsignedInt(mFormId);
    stream.writeOptional(mDataInstanceId, &BinaryStream::writeUnsignedInt);
}

Result<> ClientboundDataDrivenUIShowScreenPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mScreenId); !status) return status;
    if (auto status = stream.readUnsignedInt(mFormId); !status) return status;
    return stream.readOptional(mDataInstanceId, &ReadOnlyBinaryStream::readUnsignedInt);
}

} // namespace sculk::protocol::inline abi_v944
