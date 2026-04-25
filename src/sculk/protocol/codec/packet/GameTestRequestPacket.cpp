// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/GameTestRequestPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds GameTestRequestPacket::getId() const noexcept { return MinecraftPacketIds::GameTestRequest; }

std::string_view GameTestRequestPacket::getName() const noexcept { return "GameTestRequestPacket"; }

void GameTestRequestPacket::write(BinaryStream& stream) const {
    stream.writeVarInt(mMaxTestsPerBatch);
    stream.writeVarInt(mRepeatCount);
    stream.writeByte(mRotation);
    stream.writeBool(mStopOnFailed);
    mTestPos.write(stream);
    stream.writeVarInt(mTestsPerRow);
    stream.writeString(mTestName);
}

Result<> GameTestRequestPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mMaxTestsPerBatch); !status) return status;
    if (auto status = stream.readVarInt(mRepeatCount); !status) return status;
    if (auto status = stream.readByte(mRotation); !status) return status;
    if (auto status = stream.readBool(mStopOnFailed); !status) return status;
    if (auto status = mTestPos.read(stream); !status) return status;
    if (auto status = stream.readVarInt(mTestsPerRow); !status) return status;
    return stream.readString(mTestName);
}

} // namespace sculk::protocol::inline abi_v944
