// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/SendPartyDestinationCookiePacket.hpp"
#include "../utility/EnumName.hpp"
#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
#include "../utility/Format.hpp"
#endif

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

MinecraftPacketIds SendPartyDestinationCookiePacket::getId() const noexcept {
    return MinecraftPacketIds::SendPartyDestinationCookie;
}

std::string_view SendPartyDestinationCookiePacket::getName() const noexcept {
    return "SendPartyDestinationCookiePacket";
}

void SendPartyDestinationCookiePacket::write(BinaryStream& stream) const {
    stream.writeString(mCookie);
    utils::writeEnumName(stream, mIntent);
    stream.writeString(mDestinationName);
}

Result<> SendPartyDestinationCookiePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mCookie));
    _SCULK_READ(utils::readEnumName(stream, mIntent));
    return stream.readString(mDestinationName);
}

#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
std::string SendPartyDestinationCookiePacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mCookie),
        SCULK_FORMAT_FIELD(mIntent),
        SCULK_FORMAT_FIELD(mDestinationName)
    );
}
#endif

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
