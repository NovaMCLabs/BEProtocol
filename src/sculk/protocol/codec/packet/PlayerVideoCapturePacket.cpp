// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PlayerVideoCapturePacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds PlayerVideoCapturePacket::getId() const noexcept { return MinecraftPacketIds::PlayerVideoCapture; }

std::string_view PlayerVideoCapturePacket::getName() const noexcept { return "PlayerVideoCapturePacket"; }

void PlayerVideoCapturePacket::write(BinaryStream& stream) const {
    stream.writeVariantIndex<std::uint8_t>(mParams, &BinaryStream::writeByte);
    std::visit(
        Overload{
            [&](const StartVideoCapture& data) {
                stream.writeUnsignedInt(data.mFrameRate);
                stream.writeString(data.mFilePrefix);
            },
            [&](const StopVideoCapture&) {},
        },
        mParams
    );
}

Result<> PlayerVideoCapturePacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVariantIndex<std::uint8_t>(mParams, &ReadOnlyBinaryStream::readByte); !status)
        return status;
    return std::visit(
        Overload{
            [&](StartVideoCapture& data) {
                if (auto status = stream.readUnsignedInt(data.mFrameRate); !status) return status;
                return stream.readString(data.mFilePrefix);
            },
            [&](StopVideoCapture&) { return Result<>{}; },
        },
        mParams
    );
}

} // namespace sculk::protocol::inline abi_v944
