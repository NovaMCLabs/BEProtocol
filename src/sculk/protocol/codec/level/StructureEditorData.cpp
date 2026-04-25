// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/level/StructureEditorData.hpp"

namespace sculk::protocol::inline abi_v944 {

void StructureEditorData::write(BinaryStream& stream) const {
    stream.writeString(mStructureName);
    stream.writeString(mFilteredStructureName);
    stream.writeString(mDataField);
    stream.writeBool(mIncludePlayer);
    stream.writeBool(mShowBoundingBox);
    stream.writeVarInt(mStructureBlockType);
    mStructureSettings.write(stream);
    stream.writeVarInt(mRedstoneSaveMode);
}

Result<> StructureEditorData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mStructureName); !status) return status;
    if (auto status = stream.readString(mFilteredStructureName); !status) return status;
    if (auto status = stream.readString(mDataField); !status) return status;
    if (auto status = stream.readBool(mIncludePlayer); !status) return status;
    if (auto status = stream.readBool(mShowBoundingBox); !status) return status;
    if (auto status = stream.readVarInt(mStructureBlockType); !status) return status;
    if (auto status = mStructureSettings.read(stream); !status) return status;
    return stream.readVarInt(mRedstoneSaveMode);
}

} // namespace sculk::protocol::inline abi_v944
