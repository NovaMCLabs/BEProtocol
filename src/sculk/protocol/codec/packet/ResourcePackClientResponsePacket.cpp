// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ResourcePackClientResponsePacket.hpp"
#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
#include "../utility/Format.hpp"
#endif

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

MinecraftPacketIds ResourcePackClientResponsePacket::getId() const noexcept {
    return MinecraftPacketIds::ResourcePackClientResponse;
}

std::string_view ResourcePackClientResponsePacket::getName() const noexcept {
    return "ResourcePackClientResponsePacket";
}

void ResourcePackClientResponsePacket::write(BinaryStream& stream) const {
    stream.writeByte(mResponse);
    stream.writeArray(mPackIds, &BinaryStream::writeUnsignedShort, &BinaryStream::writeString);
}

Result<> ResourcePackClientResponsePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readByte(mResponse));
    return stream.readArray(mPackIds, &ReadOnlyBinaryStream::readUnsignedShort, &ReadOnlyBinaryStream::readString);
}

#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
std::string ResourcePackClientResponsePacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mResponse), SCULK_FORMAT_FIELD(mPackIds));
}
#endif

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
