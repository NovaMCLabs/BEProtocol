// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/biome/BiomeNoiseGradientSurfaceData.hpp"

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

void BiomeNoiseGradientSurfaceData::SerializedNoiseBlockSpecifier::write(BinaryStream& stream) const {
    stream.writeString(mNoise);
    stream.writeFloat(mThreshold);
    mRange.write(stream);
    stream.writeUnsignedInt(mBlock);
}

Result<> BiomeNoiseGradientSurfaceData::SerializedNoiseBlockSpecifier::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mNoise));
    _SCULK_READ(stream.readFloat(mThreshold));
    _SCULK_READ(mRange.read(stream));
    return stream.readUnsignedInt(mBlock);
}

void BiomeNoiseGradientSurfaceData::write(BinaryStream& stream) const {
    stream.writeArray(mNonReplaceableBlocks, &BinaryStream::writeUnsignedInt);
    stream.writeArray(mGradientBlocks, &SerializedNoiseBlockSpecifier::write);
    stream.writeString(mNoiseSeed);
    stream.writeSignedInt(mFirstOctave);
    stream.writeArray(mAmplitudes, &BinaryStream::writeFloat);
}

Result<> BiomeNoiseGradientSurfaceData::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readArray(mNonReplaceableBlocks, &ReadOnlyBinaryStream::readUnsignedInt));
    _SCULK_READ(stream.readArray(mGradientBlocks, &SerializedNoiseBlockSpecifier::read));
    _SCULK_READ(stream.readString(mNoiseSeed));
    _SCULK_READ(stream.readSignedInt(mFirstOctave));
    return stream.readArray(mAmplitudes, &ReadOnlyBinaryStream::readFloat);
}

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE