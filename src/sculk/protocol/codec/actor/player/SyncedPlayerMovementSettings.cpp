// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/actor/player/SyncedPlayerMovementSettings.hpp"

namespace sculk::protocol::inline abi_v944 {

void SyncedPlayerMovementSettings::write(BinaryStream& stream) const {
    stream.writeVarInt(mRewindHistorySize);
    stream.writeBool(mServerAuthBlockBreaking);
}

Result<> SyncedPlayerMovementSettings::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mRewindHistorySize); !status) return status;
    return stream.readBool(mServerAuthBlockBreaking);
}

} // namespace sculk::protocol::inline abi_v944
