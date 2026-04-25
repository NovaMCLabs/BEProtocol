// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/actor/attribute/Attribute.hpp"

namespace sculk::protocol::inline abi_v944 {

void Attribute::Modifier::write(BinaryStream& stream) const {
    stream.writeString(mId);
    stream.writeString(mName);
    stream.writeFloat(mAmount);
    stream.writeSignedInt(mOperation);
    stream.writeSignedInt(mOperand);
    stream.writeBool(mIsSerializable);
}

Result<> Attribute::Modifier::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mId); !status) return status;
    if (auto status = stream.readString(mName); !status) return status;
    if (auto status = stream.readFloat(mAmount); !status) return status;
    if (auto status = stream.readSignedInt(mOperation); !status) return status;
    if (auto status = stream.readSignedInt(mOperand); !status) return status;
    return stream.readBool(mIsSerializable);
}

void Attribute::write(BinaryStream& stream) const {
    stream.writeFloat(mMinValue);
    stream.writeFloat(mMaxValue);
    stream.writeFloat(mCurrentValue);
    stream.writeFloat(mDefaultMinValue);
    stream.writeFloat(mDefaultMaxValue);
    stream.writeFloat(mDefaultValue);
    stream.writeString(mName);
    stream.writeArray(mModifiers, &Attribute::Modifier::write);
}

Result<> Attribute::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readFloat(mMinValue); !status) return status;
    if (auto status = stream.readFloat(mMaxValue); !status) return status;
    if (auto status = stream.readFloat(mCurrentValue); !status) return status;
    if (auto status = stream.readFloat(mDefaultMinValue); !status) return status;
    if (auto status = stream.readFloat(mDefaultMaxValue); !status) return status;
    if (auto status = stream.readFloat(mDefaultValue); !status) return status;
    if (auto status = stream.readString(mName); !status) return status;
    return stream.readArray(mModifiers, &Attribute::Modifier::read);
}

} // namespace sculk::protocol::inline abi_v944
