// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CreativeContentPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void CreativeContentPacket::WriteEntry::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt(mNetId);
    mItem.write(stream);
    stream.writeUnsignedVarInt(mGroupIndex);
}

Result<> CreativeContentPacket::WriteEntry::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt(mNetId); !status) return status;
    if (auto status = mItem.read(stream); !status) return status;
    return stream.readUnsignedVarInt(mGroupIndex);
}

void CreativeContentPacket::Group::write(BinaryStream& stream) const {
    stream.writeSignedInt(mCategory);
    stream.writeString(mName);
    mIcon.write(stream);
}

Result<> CreativeContentPacket::Group::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readSignedInt(mCategory); !status) return status;
    if (auto status = stream.readString(mName); !status) return status;
    return mIcon.read(stream);
}

MinecraftPacketIds CreativeContentPacket::getId() const noexcept { return MinecraftPacketIds::CreativeContent; }

std::string_view CreativeContentPacket::getName() const noexcept { return "CreativeContentPacket"; }

void CreativeContentPacket::write(BinaryStream& stream) const {
    stream.writeArray(mGroups, &Group::write);
    stream.writeArray(mWriteEntries, &WriteEntry::write);
}

Result<> CreativeContentPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readArray(mGroups, &Group::read); !status) return status;
    return stream.readArray(mWriteEntries, &WriteEntry::read);
}

} // namespace sculk::protocol::inline abi_v944
