// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CameraPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds CameraPacket::getId() const noexcept { return MinecraftPacketIds::Camera; }

std::string_view CameraPacket::getName() const noexcept { return "CameraPacket"; }

void CameraPacket::write(BinaryStream& stream) const {
    stream.writeVarInt64(mCameraId);
    stream.writeVarInt64(mTargetPlayerId);
}

Result<> CameraPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt64(mCameraId); !status) return status;
    return stream.readVarInt64(mTargetPlayerId);
}

} // namespace sculk::protocol::inline abi_v944
