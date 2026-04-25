// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/command/CommandChainedSubcommandData.hpp"

namespace sculk::protocol::inline abi_v944 {

void CommandChainedSubcommandData::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeArray(mValues, [](BinaryStream& stream, const std::pair<std::uint32_t, std::uint32_t>& value) {
        stream.writeUnsignedVarInt(value.first);
        stream.writeUnsignedVarInt(value.second);
    });
}

Result<> CommandChainedSubcommandData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    return stream.readArray(mValues, [](ReadOnlyBinaryStream& stream, std::pair<std::uint32_t, std::uint32_t>& value) {
        if (auto status = stream.readUnsignedVarInt(value.first); !status) return status;
        if (auto status = stream.readUnsignedVarInt(value.second); !status) return status;
        return Result<>{};
    });
}

} // namespace sculk::protocol::inline abi_v944
