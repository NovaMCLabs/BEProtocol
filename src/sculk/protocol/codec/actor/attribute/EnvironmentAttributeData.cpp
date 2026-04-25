// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/actor/attribute/EnvironmentAttributeData.hpp"

namespace sculk::protocol::inline abi_v944 {

void EnvironmentAttributeData::write(BinaryStream& stream) const {
    stream.writeString(mAttributeName);
    stream.writeOptional(mFromAttribute, &AttributeData::write);
    mAttribute.write(stream);
    stream.writeOptional(mToAttribute, &AttributeData::write);
    stream.writeUnsignedInt(mCurrentTransitionTicks);
    stream.writeUnsignedInt(mTotalTransitionTicks);
    stream.writeEnum(mEasing, &BinaryStream::writeSignedInt);
}

Result<> EnvironmentAttributeData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mAttributeName); !status) return status;
    if (auto status = stream.readOptional(mFromAttribute, &AttributeData::read); !status) return status;
    if (auto status = mAttribute.read(stream); !status) return status;
    if (auto status = stream.readOptional(mToAttribute, &AttributeData::read); !status) return status;
    if (auto status = stream.readUnsignedInt(mCurrentTransitionTicks); !status) return status;
    if (auto status = stream.readUnsignedInt(mTotalTransitionTicks); !status) return status;
    return stream.readEnum(mEasing, &ReadOnlyBinaryStream::readSignedInt);
}

} // namespace sculk::protocol::inline abi_v944
