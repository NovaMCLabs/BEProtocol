// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/AvailableCommandsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds AvailableCommandsPacket::getId() const noexcept { return MinecraftPacketIds::AvailableCommands; }

std::string_view AvailableCommandsPacket::getName() const noexcept { return "AvailableCommandsPacket"; }

void AvailableCommandsPacket::write(BinaryStream& stream) const {
    stream.writeArray(mEnumValues, &BinaryStream::writeString);
    stream.writeArray(mChainedSubcommandsValues, &BinaryStream::writeString);
    stream.writeArray(mPostFixes, &BinaryStream::writeString);
    stream.writeArray(mEnumData, &CommandEnumData::write);
    stream.writeArray(mChainedSubcommandData, &CommandChainedSubcommandData::write);
    stream.writeArray(mCommands, &CommandData::write);
    stream.writeArray(mSoftEnums, &CommandSoftEnumData::write);
    stream.writeArray(mConstraints, &CommandConstrainedValueData::write);
}

Result<> AvailableCommandsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readArray(mEnumValues, &ReadOnlyBinaryStream::readString); !status) return status;
    if (auto status = stream.readArray(mChainedSubcommandsValues, &ReadOnlyBinaryStream::readString); !status)
        return status;
    if (auto status = stream.readArray(mPostFixes, &ReadOnlyBinaryStream::readString); !status) return status;
    if (auto status = stream.readArray(mEnumData, &CommandEnumData::read); !status) return status;
    if (auto status = stream.readArray(mChainedSubcommandData, &CommandChainedSubcommandData::read); !status)
        return status;
    if (auto status = stream.readArray(mCommands, &CommandData::read); !status) return status;
    if (auto status = stream.readArray(mSoftEnums, &CommandSoftEnumData::read); !status) return status;
    return stream.readArray(mConstraints, &CommandConstrainedValueData::read);
}

} // namespace sculk::protocol::inline abi_v944
