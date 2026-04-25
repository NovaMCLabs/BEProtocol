// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/GameTestResultsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds GameTestResultsPacket::getId() const noexcept { return MinecraftPacketIds::GameTestResults; }

std::string_view GameTestResultsPacket::getName() const noexcept { return "GameTestResultsPacket"; }

void GameTestResultsPacket::write(BinaryStream& stream) const {
    stream.writeBool(mSucceeded);
    stream.writeString(mError);
    stream.writeString(mTestName);
}

Result<> GameTestResultsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readBool(mSucceeded); !status) return status;
    if (auto status = stream.readString(mError); !status) return status;
    return stream.readString(mTestName);
}

} // namespace sculk::protocol::inline abi_v944
