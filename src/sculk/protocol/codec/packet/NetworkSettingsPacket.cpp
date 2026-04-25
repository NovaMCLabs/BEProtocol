// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/NetworkSettingsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds NetworkSettingsPacket::getId() const noexcept { return MinecraftPacketIds::NetworkSettings; }

std::string_view NetworkSettingsPacket::getName() const noexcept { return "NetworkSettingsPacket"; }

void NetworkSettingsPacket::write(BinaryStream& stream) const {
    stream.writeUnsignedShort(mCompressionThreshold);
    stream.writeEnum(mCompressionAlgorithm, &BinaryStream::writeUnsignedShort);
    stream.writeBool(mClientThrottleEnabled);
    stream.writeByte(mClientThrottleThreshold);
    stream.writeFloat(mClientThrottleScalar);
}

Result<> NetworkSettingsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readUnsignedShort(mCompressionThreshold); !status) return status;
    if (auto status = stream.readEnum(mCompressionAlgorithm, &ReadOnlyBinaryStream::readUnsignedShort); !status)
        return status;
    if (auto status = stream.readBool(mClientThrottleEnabled); !status) return status;
    if (auto status = stream.readByte(mClientThrottleThreshold); !status) return status;
    return stream.readFloat(mClientThrottleScalar);
}

} // namespace sculk::protocol::inline abi_v944
