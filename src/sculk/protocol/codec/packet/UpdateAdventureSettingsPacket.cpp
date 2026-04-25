// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/UpdateAdventureSettingsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds UpdateAdventureSettingsPacket::getId() const noexcept {
    return MinecraftPacketIds::UpdateAdventureSettings;
}

std::string_view UpdateAdventureSettingsPacket::getName() const noexcept { return "UpdateAdventureSettingsPacket"; }

void UpdateAdventureSettingsPacket::write(BinaryStream& stream) const {
    stream.writeBool(mNoPvM);
    stream.writeBool(mNoMvP);
    stream.writeBool(mImmutableWorld);
    stream.writeBool(mShowNameTags);
    stream.writeBool(mAutoJump);
}

Result<> UpdateAdventureSettingsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readBool(mNoPvM); !status) return status;
    if (auto status = stream.readBool(mNoMvP); !status) return status;
    if (auto status = stream.readBool(mImmutableWorld); !status) return status;
    if (auto status = stream.readBool(mShowNameTags); !status) return status;
    return stream.readBool(mAutoJump);
}

} // namespace sculk::protocol::inline abi_v944
