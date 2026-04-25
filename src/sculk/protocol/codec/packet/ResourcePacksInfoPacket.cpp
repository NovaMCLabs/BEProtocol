// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ResourcePacksInfoPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds ResourcePacksInfoPacket::getId() const noexcept { return MinecraftPacketIds::ResourcePacksInfo; }

std::string_view ResourcePacksInfoPacket::getName() const noexcept { return "ResourcePacksInfoPacket"; }

void ResourcePacksInfoPacket::write(BinaryStream& stream) const {
    stream.writeBool(mResourcePackRequired);
    stream.writeBool(mHasAddonPacks);
    stream.writeBool(mHasScripts);
    stream.writeBool(mIsVibrantVisualsForceDisabled);
    mWorldTemplateId.write(stream);
    stream.writeString(mWorldTemplateVersion);
    stream.writeUnsignedShort(static_cast<std::uint16_t>(mResourcePacks.size()));
    for (const auto& pack : mResourcePacks) {
        pack.write(stream);
    }
}

Result<> ResourcePacksInfoPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readBool(mResourcePackRequired); !status) return status;
    if (auto status = stream.readBool(mHasAddonPacks); !status) return status;
    if (auto status = stream.readBool(mHasScripts); !status) return status;
    if (auto status = stream.readBool(mIsVibrantVisualsForceDisabled); !status) return status;
    if (auto status = mWorldTemplateId.read(stream); !status) return status;
    if (auto status = stream.readString(mWorldTemplateVersion); !status) return status;
    std::uint16_t size{};
    if (auto status = stream.readUnsignedShort(size); !status) return status;
    mResourcePacks.resize(size);
    for (auto& pack : mResourcePacks) {
        if (auto status = pack.read(stream); !status) return status;
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v944
