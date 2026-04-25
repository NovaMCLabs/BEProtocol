// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AddActorPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds AddActorPacket::getId() const noexcept { return MinecraftPacketIds::AddActor; }

std::string_view AddActorPacket::getName() const noexcept { return "AddActorPacket"; }

void AddActorPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mActorUniqueId);
    stream.writeUnsignedVarInt64(mActorRuntimeId);
    stream.writeString(mIdentifier);
    mPosition.write(stream);
    mVelocity.write(stream);
    mRotation.write(stream);
    stream.writeFloat(mYHeadRotation);
    stream.writeFloat(mYBodyRotation);
    stream.writeArray(mAttributes, &SyncedAttribute::write);
    mMetaData.write(stream);
    mSynchedProperties.write(stream);
    stream.writeArray(mActorLinks, &ActorLink::write);
}

Result<> AddActorPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mActorUniqueId); !status) return status;
    if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    if (auto status = stream.readString(mIdentifier); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = mVelocity.read(stream); !status) return status;
    if (auto status = mRotation.read(stream); !status) return status;
    if (auto status = stream.readFloat(mYHeadRotation); !status) return status;
    if (auto status = stream.readFloat(mYBodyRotation); !status) return status;
    if (auto status = stream.readArray(mAttributes, &SyncedAttribute::read); !status) return status;
    if (auto status = mMetaData.read(stream); !status) return status;
    if (auto status = mSynchedProperties.read(stream); !status) return status;
    return stream.readArray(mActorLinks, &ActorLink::read);
}

} // namespace sculk::protocol::inline abi_v944
