// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/PartyDestinationCookieResponsePacket.hpp"
#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
#include "../utility/Format.hpp"
#endif

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

MinecraftPacketIds PartyDestinationCookieResponsePacket::getId() const noexcept {
    return MinecraftPacketIds::PartyDestinationCookieResponse;
}

std::string_view PartyDestinationCookieResponsePacket::getName() const noexcept {
    return "PartyDestinationCookieResponsePacket";
}

void PartyDestinationCookieResponsePacket::write(BinaryStream& stream) const {
    stream.writeString(mCookie);
    stream.writeBool(mAccepted);
}

Result<> PartyDestinationCookieResponsePacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readString(mCookie));
    return stream.readBool(mAccepted);
}

#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
std::string PartyDestinationCookieResponsePacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mCookie), SCULK_FORMAT_FIELD(mAccepted));
}
#endif

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
