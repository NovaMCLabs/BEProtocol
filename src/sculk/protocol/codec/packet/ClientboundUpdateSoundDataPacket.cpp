// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientboundUpdateSoundDataPacket.hpp"
#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
#include "../utility/Format.hpp"
#endif

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

MinecraftPacketIds ClientboundUpdateSoundDataPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientboundUpdateSoundData;
}

std::string_view ClientboundUpdateSoundDataPacket::getName() const noexcept {
    return "ClientboundUpdateSoundDataPacket";
}

void ClientboundUpdateSoundDataPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedInt64(mHandle);
    stream.writeString(mSoundEvent);
}

Result<> ClientboundUpdateSoundDataPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readUnsignedInt64(mHandle));
    _SCULK_READ(stream.readString(mSoundEvent));
    return {};
}

#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
std::string ClientboundUpdateSoundDataPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mHandle), SCULK_FORMAT_FIELD(mSoundEvent));
}
#endif

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
