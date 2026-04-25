// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/TextPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds TextPacket::getId() const noexcept { return MinecraftPacketIds::Text; }

std::string_view TextPacket::getName() const noexcept { return "TextPacket"; }

void TextPacket::write(BinaryStream& stream) const {
    stream.writeBool(mLocalize);
    stream.writeVariantIndex<std::uint8_t>(mBody, &BinaryStream::writeByte);
    stream.writeEnum(mType, &BinaryStream::writeByte);
    std::visit(
        Overload{
            [&](const TextPacket::MessageOnly& body) { stream.writeString(body.mMessage); },
            [&](const TextPacket::AuthorAndMessage& body) {
                stream.writeString(body.mPlayerName);
                stream.writeString(body.mMessage);
            },
            [&](const TextPacket::MessageAndParams& body) {
                stream.writeString(body.mMessage);
                stream.writeArray(body.mParameters, &BinaryStream::writeString);
            },
        },
        mBody
    );
    stream.writeString(mXuid);
    stream.writeString(mPlatformId);
    stream.writeString(mFilteredMessage);
}

Result<> TextPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readBool(mLocalize); !status) return status;
    if (auto status = stream.readVariantIndex<std::uint8_t>(mBody, &ReadOnlyBinaryStream::readByte); !status)
        return status;
    if (auto status = stream.readEnum(mType, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (auto status = std::visit(
            Overload{
                [&](TextPacket::MessageOnly& body) { return stream.readString(body.mMessage); },
                [&](TextPacket::AuthorAndMessage& body) {
                    if (auto status = stream.readString(body.mPlayerName); !status) return status;
                    return stream.readString(body.mMessage);
                },
                [&](TextPacket::MessageAndParams& body) {
                    if (auto status = stream.readString(body.mMessage); !status) return status;
                    return stream.readArray(body.mParameters, &ReadOnlyBinaryStream::readString);
                },
            },
            mBody
        );
        !status)
        return status;
    if (auto status = stream.readString(mXuid); !status) return status;
    if (auto status = stream.readString(mPlatformId); !status) return status;
    return stream.readString(mFilteredMessage);
}

} // namespace sculk::protocol::inline abi_v944
