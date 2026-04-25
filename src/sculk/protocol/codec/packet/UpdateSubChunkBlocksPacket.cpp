// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateSubChunkBlocksPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UpdateSubChunkBlocksPacket::getId() const noexcept {
    return MinecraftPacketIds::UpdateSubChunkBlocks;
}

std::string_view UpdateSubChunkBlocksPacket::getName() const noexcept { return "UpdateSubChunkBlocksPacket"; }

void UpdateSubChunkBlocksPacket::write(BinaryStream& stream) const {
    mSubChunkBlockPosition.write(stream);
    stream.writeArray(mBlocksChangeStandards, &SubChunkBlockChangeInfo::write);
    stream.writeArray(mBlocksChangeExtras, &SubChunkBlockChangeInfo::write);
}

Result<> UpdateSubChunkBlocksPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mSubChunkBlockPosition.read(stream); !status) return status;
    if (auto status = stream.readArray(mBlocksChangeStandards, &SubChunkBlockChangeInfo::read); !status) return status;
    return stream.readArray(mBlocksChangeExtras, &SubChunkBlockChangeInfo::read);
}

} // namespace sculk::protocol::inline abi_v944
