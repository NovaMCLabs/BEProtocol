// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/MobArmorEquipmentPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds MobArmorEquipmentPacket::getId() const noexcept { return MinecraftPacketIds::MobArmorEquipment; }

std::string_view MobArmorEquipmentPacket::getName() const noexcept { return "MobArmorEquipmentPacket"; }

void MobArmorEquipmentPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedVarInt64(mRuntimeId);
    mHead.write(stream);
    mTorso.write(stream);
    mLegs.write(stream);
    mFeet.write(stream);
    mBody.write(stream);
}

Result<> MobArmorEquipmentPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedVarInt64(mRuntimeId); !status) return status;
    if (auto status = mHead.read(stream); !status) return status;
    if (auto status = mTorso.read(stream); !status) return status;
    if (auto status = mLegs.read(stream); !status) return status;
    if (auto status = mFeet.read(stream); !status) return status;
    return mBody.read(stream);
}

} // namespace sculk::protocol::inline abi_v944
