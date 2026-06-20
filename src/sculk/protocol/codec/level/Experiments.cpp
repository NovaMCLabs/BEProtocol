// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/Experiments.hpp"

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

void Experiments::Experiment::write(BinaryStream& stream) const {
    stream.writeString(mName);
    stream.writeBool(mEnabled);
}

Result<> Experiments::Experiment::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mName));
    return stream.readBool(mEnabled);
}

void Experiments::write(BinaryStream& stream) const {
    stream.writeArray(mExperiments, &BinaryStream::writeUnsignedInt, &Experiment::write);
    stream.writeBool(mEverToggled);
}

Result<> Experiments::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readArray(mExperiments, &ReadOnlyBinaryStream::readUnsignedInt, &Experiment::read));
    return stream.readBool(mEverToggled);
}

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
