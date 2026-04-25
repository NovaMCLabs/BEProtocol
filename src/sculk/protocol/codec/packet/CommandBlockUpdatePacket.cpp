// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CommandBlockUpdatePacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds CommandBlockUpdatePacket::getId() const noexcept { return MinecraftPacketIds::CommandBlockUpdate; }

std::string_view CommandBlockUpdatePacket::getName() const noexcept { return "CommandBlockUpdatePacket"; }

void CommandBlockUpdatePacket::write(BinaryStream& stream) const {
    stream.writeBool(mIsBlock);
    if (mIsBlock) {
        mBlockPosition.write(stream);
        stream.writeUnsignedVarInt(mCommandBlockMode);
        stream.writeBool(mRedstoneMode);
        stream.writeBool(mConditional);
    } else {
        stream.writeUnsignedVarInt64(mActorRuntimeId);
    }
    stream.writeString(mCommand);
    stream.writeString(mLastOutput);
    stream.writeString(mName);
    stream.writeString(mFilteredName);
    stream.writeBool(mTrackOutput);
    stream.writeUnsignedInt(mTickDelay);
    stream.writeBool(mExecuteOnFirstTick);
}

Result<> CommandBlockUpdatePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readBool(mIsBlock));
    if (mIsBlock) {
        _SCULK_READ(mBlockPosition.read(stream));
        _SCULK_READ(stream.readUnsignedVarInt(mCommandBlockMode));
        _SCULK_READ(stream.readBool(mRedstoneMode));
        _SCULK_READ(stream.readBool(mConditional));
    } else {
        _SCULK_READ(stream.readUnsignedVarInt64(mActorRuntimeId));
    }
    _SCULK_READ(stream.readString(mCommand));
    _SCULK_READ(stream.readString(mLastOutput));
    _SCULK_READ(stream.readString(mName));
    _SCULK_READ(stream.readString(mFilteredName));
    _SCULK_READ(stream.readBool(mTrackOutput));
    _SCULK_READ(stream.readUnsignedInt(mTickDelay));
    return stream.readBool(mExecuteOnFirstTick);
}

} // namespace sculk::protocol::inline abi_v975
