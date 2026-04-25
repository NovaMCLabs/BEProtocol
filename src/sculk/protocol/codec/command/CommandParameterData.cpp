// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/command/CommandParameterData.hpp"

namespace sculk::protocol::inline abi_v944 {

void CommandParameterData::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeUnsignedInt(mParseSymbol);
    stream.writeBool(mIsOptional);
    stream.writeByte(mOptions);
}

Result<> CommandParameterData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readUnsignedInt(mParseSymbol); !status) return status;
    if (auto status = stream.readBool(mIsOptional); !status) return status;
    return stream.readByte(mOptions);
}

} // namespace sculk::protocol::inline abi_v944
