// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/actor/attribute/BoolAttributeData.hpp"

namespace sculk::protocol::inline abi_v944 {

void BoolAttributeData::write(BinaryStream& stream) const {
    stream.writeBool(mValue);
    stream.writeEnum(mOperation, &BinaryStream::writeSignedInt);
}

Result<> BoolAttributeData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readBool(mValue); !status) return status;
    return stream.readEnum(mOperation, &ReadOnlyBinaryStream::readSignedInt);
}

} // namespace sculk::protocol::inline abi_v944
