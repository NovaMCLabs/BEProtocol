// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SetScoreboardIdentityPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds SetScoreboardIdentityPacket::getId() const noexcept {
    return MinecraftPacketIds::SetScoreboardIdentity;
}

std::string_view SetScoreboardIdentityPacket::getName() const noexcept { return "SetScoreboardIdentityPacket"; }

void SetScoreboardIdentityPacket::write(BinaryStream& stream) const {
    stream.writeEnum(mType, &BinaryStream::writeByte);
    stream.writeArray(mSetScoreboardIdentities, [&](const ScoreboardIdentity& data) {
        stream.writeVarInt64(data.mScoreboardId);
        if (mType == Type::Update) {
            stream.writeVarInt64(data.mPlayerUniqueId);
        }
    });
}

Result<> SetScoreboardIdentityPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readByte); !status) return status;
    return stream.readArray(mSetScoreboardIdentities, [&](ScoreboardIdentity& data) {
        if (auto status = stream.readVarInt64(data.mScoreboardId); !status) return status;
        if (mType == Type::Update) {
            if (auto status = stream.readVarInt64(data.mPlayerUniqueId); !status) return status;
        } else {
            data.mPlayerUniqueId = 0;
        }
        return Result<>{};
    });
}

} // namespace sculk::protocol::inline abi_v944
