// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/actor/attribute/FloatAttributeData.hpp"

namespace sculk::protocol::inline abi_v944 {

void FloatAttributeData::write(BinaryStream& stream) const {
    stream.writeFloat(mValue);
    stream.writeEnum(mOperation, &BinaryStream::writeSignedInt);
    stream.writeFloat(mConstraintMin);
    stream.writeFloat(mConstraintMax);
}

Result<> FloatAttributeData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mValue); !status) return status;
    if (auto status = stream.readEnum(mOperation, &ReadOnlyBinaryStream::readSignedInt); !status) return status;
    if (auto status = stream.readFloat(mConstraintMin); !status) return status;
    return stream.readFloat(mConstraintMax);
}

} // namespace sculk::protocol::inline abi_v944
