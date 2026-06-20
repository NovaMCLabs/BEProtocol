// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ServerPresenceInfoPacket.hpp"
#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
#include "../utility/Format.hpp"
#endif

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

MinecraftPacketIds ServerPresenceInfoPacket::getId() const noexcept { return MinecraftPacketIds::ServerPresenceInfo; }

std::string_view ServerPresenceInfoPacket::getName() const noexcept { return "ServerPresenceInfoPacket"; }

void ServerPresenceInfoPacket::write(BinaryStream& stream) const { mPresenceConfiguration.write(stream); }

Result<> ServerPresenceInfoPacket::read(ReadOnlyBinaryStream& stream) { return mPresenceConfiguration.read(stream); }

#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
std::string ServerPresenceInfoPacket::toString() const {
    return SCULK_FORMAT_PACKET(SCULK_FORMAT_FIELD(mPresenceConfiguration));
}
#endif

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE
