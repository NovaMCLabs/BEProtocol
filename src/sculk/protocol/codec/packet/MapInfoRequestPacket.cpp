// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/MapInfoRequestPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void MapInfoRequestPacket::ClientPixel::write(BinaryStream& stream) const {
    stream.writeUnsignedInt(mPixel);
    stream.writeUnsignedShort(mIndex);
}

Result<> MapInfoRequestPacket::ClientPixel::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedInt(mPixel); !status) return status;
    return stream.readUnsignedShort(mIndex);
}

MinecraftPacketIds MapInfoRequestPacket::getId() const noexcept { return MinecraftPacketIds::MapInfoRequest; }

std::string_view MapInfoRequestPacket::getName() const noexcept { return "MapInfoRequestPacket"; }

void MapInfoRequestPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mMapUniqueId);
    stream.writeUnsignedInt(static_cast<std::uint32_t>(mClientPixels.size()));
    for (const auto& pixel : mClientPixels) {
        pixel.write(stream);
    }
}

Result<> MapInfoRequestPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mMapUniqueId); !status) return status;
    std::uint32_t pixelCount{};
    if (auto status = stream.readUnsignedInt(pixelCount); !status) return status;
    mClientPixels.clear();
    mClientPixels.resize(pixelCount);
    for (auto& pixel : mClientPixels) {
        if (auto status = pixel.read(stream); !status) return status;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
