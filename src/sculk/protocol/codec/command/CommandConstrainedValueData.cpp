// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/command/CommandConstrainedValueData.hpp"

namespace sculk::protocol::inline abi_v944 {

void CommandConstrainedValueData::write(BinaryStream& stream) const {
    stream.writeUnsignedInt(mEnumValueSymbol);
    stream.writeUnsignedInt(mEnumSymbol);
    stream.writeArray(mConstraintIndices, &BinaryStream::writeByte);
}

Result<> CommandConstrainedValueData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedInt(mEnumValueSymbol); !status) return status;
    if (auto status = stream.readUnsignedInt(mEnumSymbol); !status) return status;
    return stream.readArray(mConstraintIndices, &ReadOnlyBinaryStream::readByte);
}

} // namespace sculk::protocol::inline abi_v944
