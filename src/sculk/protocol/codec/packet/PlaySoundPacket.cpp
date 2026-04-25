// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlaySoundPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PlaySoundPacket::getId() const noexcept { return MinecraftPacketIds::PlaySound; }

std::string_view PlaySoundPacket::getName() const noexcept { return "PlaySoundPacket"; }

void PlaySoundPacket::write(BinaryStream& stream) const {
    stream.writeString(mName);
    mPosition.write(stream);
    stream.writeFloat(mVolume);
    stream.writeFloat(mPitch);
}

Result<> PlaySoundPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = mPosition.read(stream); !status) return status;
    if (auto status = stream.readFloat(mVolume); !status) return status;
    return stream.readFloat(mPitch);
}

} // namespace sculk::protocol::inline abi_v944
