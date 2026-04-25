// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientCacheBlobStatusPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ClientCacheBlobStatusPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientCacheBlobStatus;
}

std::string_view ClientCacheBlobStatusPacket::getName() const noexcept { return "ClientCacheBlobStatusPacket"; }

void ClientCacheBlobStatusPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(static_cast<std::uint32_t>(mMissingIds.size()));
    stream.writeUnsignedVarInt(static_cast<std::uint32_t>(mFoundIds.size()));
    for (const auto& id : mMissingIds) {
        stream.writeUnsignedInt64(id);
    }
    for (const auto& id : mFoundIds) {
        stream.writeUnsignedInt64(id);
    }
}

Result<> ClientCacheBlobStatusPacket::read(ReadOnlyBinaryStream& stream) {
    std::uint32_t missingSize{};
    std::uint32_t foundSize{};
    if (auto status = stream.readUnsignedVarInt(missingSize); !status) return status;
    if (auto status = stream.readUnsignedVarInt(foundSize); !status) return status;
    mMissingIds.resize(missingSize);
    for (auto& id : mMissingIds) {
        if (auto status = stream.readUnsignedInt64(id); !status) return status;
    }
    mFoundIds.resize(foundSize);
    for (auto& id : mFoundIds) {
        if (auto status = stream.readUnsignedInt64(id); !status) return status;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
