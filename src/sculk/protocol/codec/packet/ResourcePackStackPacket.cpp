// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ResourcePackStackPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void ResourcePackStackPacket::PackInfo::write(BinaryStream& stream) const {
    stream.writeString(mId);
    stream.writeString(mVersion);
    stream.writeString(mSubPackName);
}

Result<> ResourcePackStackPacket::PackInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mId); !status) return status;
    if (auto status = stream.readString(mVersion); !status) return status;
    return stream.readString(mSubPackName);
}

MinecraftPacketIds ResourcePackStackPacket::getId() const noexcept { return MinecraftPacketIds::ResourcePackStack; }

std::string_view ResourcePackStackPacket::getName() const noexcept { return "ResourcePackStackPacket"; }

void ResourcePackStackPacket::write(BinaryStream& stream) const {
    stream.writeBool(mTexturePackRequired);
    stream.writeArray(mTexturePackList, &PackInfo::write);
    stream.writeString(mBaseGameVersion);
    mExperiments.write(stream);
    stream.writeBool(mIncludeEditorPacks);
}

Result<> ResourcePackStackPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readBool(mTexturePackRequired); !status) return status;
    if (auto status = stream.readArray(mTexturePackList, &PackInfo::read); !status) return status;
    if (auto status = stream.readString(mBaseGameVersion); !status) return status;
    if (auto status = mExperiments.read(stream); !status) return status;
    return stream.readBool(mIncludeEditorPacks);
}

} // namespace sculk::protocol::inline abi_v944
