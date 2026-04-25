// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/CommandBlockUpdatePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

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
    if (auto status = stream.readBool(mIsBlock); !status) return status;
    if (mIsBlock) {
        if (auto status = mBlockPosition.read(stream); !status) return status;
        if (auto status = stream.readUnsignedVarInt(mCommandBlockMode); !status) return status;
        if (auto status = stream.readBool(mRedstoneMode); !status) return status;
        if (auto status = stream.readBool(mConditional); !status) return status;
    } else {
        if (auto status = stream.readUnsignedVarInt64(mActorRuntimeId); !status) return status;
    }
    if (auto status = stream.readString(mCommand); !status) return status;
    if (auto status = stream.readString(mLastOutput); !status) return status;
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readString(mFilteredName); !status) return status;
    if (auto status = stream.readBool(mTrackOutput); !status) return status;
    if (auto status = stream.readUnsignedInt(mTickDelay); !status) return status;
    return stream.readBool(mExecuteOnFirstTick);
}

} // namespace sculk::protocol::inline abi_v944
