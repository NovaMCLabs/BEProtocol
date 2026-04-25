// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/NetworkChunkPublisherUpdatePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds NetworkChunkPublisherUpdatePacket::getId() const noexcept {
    return MinecraftPacketIds::NetworkChunkPublisherUpdate;
}

std::string_view NetworkChunkPublisherUpdatePacket::getName() const noexcept {
    return "NetworkChunkPublisherUpdatePacket";
}

void NetworkChunkPublisherUpdatePacket::write(BinaryStream& stream) const {
    mNewPositionForView.write(stream);
    stream.writeUnsignedVarInt(mNewRadiusForView);
    stream.writeUnsignedInt(static_cast<std::uint32_t>(mServerBuiltChunksList.size()));
    for (const auto& chunkPos : mServerBuiltChunksList) {
        chunkPos.write(stream);
    }
}

Result<> NetworkChunkPublisherUpdatePacket::read(ReadOnlyBinaryStream& stream) {
    std::uint32_t count{};
    if (auto status = mNewPositionForView.read(stream); !status) return status;
    if (auto status = stream.readUnsignedVarInt(mNewRadiusForView); !status) return status;
    if (auto status = stream.readUnsignedInt(count); !status) return status;
    mServerBuiltChunksList.clear();
    mServerBuiltChunksList.resize(count);
    for (auto& chunkPos : mServerBuiltChunksList) {
        if (auto status = chunkPos.read(stream); !status) return status;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
