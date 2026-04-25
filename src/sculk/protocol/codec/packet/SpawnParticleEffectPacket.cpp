// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SpawnParticleEffectPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SpawnParticleEffectPacket::getId() const noexcept { return MinecraftPacketIds::SpawnParticleEffect; }

std::string_view SpawnParticleEffectPacket::getName() const noexcept { return "SpawnParticleEffectPacket"; }

void SpawnParticleEffectPacket::write(BinaryStream& stream) const {
    stream.writeByte(mDimensionId);
    stream.writeVarInt64(mActorUniqueId);
    mPosition.write(stream);
    stream.writeString(mEffectName);
    stream.writeOptional(mMolangVariableMap, &BinaryStream::writeString);
}

Result<> SpawnParticleEffectPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readByte(mDimensionId); !status) return status;
    if (auto status = stream.readVarInt64(mActorUniqueId); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = stream.readString(mEffectName); !status) return status;
    return stream.readOptional(mMolangVariableMap, &ReadOnlyBinaryStream::readString);
}

} // namespace sculk::protocol::inline abi_v944
