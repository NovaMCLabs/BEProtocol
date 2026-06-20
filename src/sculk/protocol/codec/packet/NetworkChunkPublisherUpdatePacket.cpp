// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/NetworkChunkPublisherUpdatePacket.hpp"
#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
#include "../utility/Format.hpp"
#endif

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

MinecraftPacketIds NetworkChunkPublisherUpdatePacket::getId() const noexcept {
    return MinecraftPacketIds::NetworkChunkPublisherUpdate;
}

std::string_view NetworkChunkPublisherUpdatePacket::getName() const noexcept {
    return "NetworkChunkPublisherUpdatePacket";
}

void NetworkChunkPublisherUpdatePacket::write(BinaryStream& stream) const {
    mNewPositionForView.write(stream);
    stream.writeUnsignedVarInt(mNewRadiusForView);
    stream.writeArray(mServerBuiltChunksList, &BinaryStream::writeUnsignedInt, &ChunkPos::write);
}

Result<> NetworkChunkPublisherUpdatePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(mNewPositionForView.read(stream));
    _SCULK_READ(stream.readUnsignedVarInt(mNewRadiusForView));
    return stream.readArray(mServerBuiltChunksList, &ReadOnlyBinaryStream::readUnsignedInt, &ChunkPos::read);
}

#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
std::string NetworkChunkPublisherUpdatePacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mNewPositionForView),
        SCULK_FORMAT_FIELD(mNewRadiusForView),
        SCULK_FORMAT_FIELD(mServerBuiltChunksList)
    );
}
#endif

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
