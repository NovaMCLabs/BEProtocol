// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/EditorNetworkPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds EditorNetworkPacket::getId() const noexcept { return MinecraftPacketIds::EditorNetwork; }

std::string_view EditorNetworkPacket::getName() const noexcept { return "EditorNetworkPacket"; }

void EditorNetworkPacket::write(BinaryStream& stream) const {
    stream.writeBool(mRouteToManager);
    stream.writeString(mRawVariantName);
    stream.writeString(mRawVariantData);
}

Result<> EditorNetworkPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readBool(mRouteToManager); !status) return status;
    if (auto status = stream.readString(mRawVariantName); !status) return status;
    return stream.readString(mRawVariantData);
}

} // namespace sculk::protocol::inline abi_v944
