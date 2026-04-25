// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/BookEditPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

MinecraftPacketIds BookEditPacket::getId() const noexcept { return MinecraftPacketIds::BookEdit; }

std::string_view BookEditPacket::getName() const noexcept { return "BookEditPacket"; }

void BookEditPacket::write(BinaryStream& stream) const {
    stream.writeVarInt(mBookSlot);
    stream.writeEnum(mAction, &BinaryStream::writeUnsignedVarInt);
    switch (mAction) {
    case Action::ReplacePage:
    case Action::AddPage:
        stream.writeVarInt(mPageIndexA);
        stream.writeString(mTextA);
        stream.writeString(mTextB);
        break;
    case Action::DeletePage:
        stream.writeVarInt(mPageIndexA);
        break;
    case Action::SwapPages:
        stream.writeVarInt(mPageIndexA);
        stream.writeVarInt(mPageIndexB);
        break;
    case Action::Finalize:
        stream.writeString(mTextA);
        stream.writeString(mTextB);
        stream.writeString(mXuid);
        break;
    default:
        break;
    }
}

Result<> BookEditPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mBookSlot); !status) return status;
    if (auto status = stream.readEnum(mAction, &ReadOnlyBinaryStream::readUnsignedVarInt); !status) return status;
    switch (mAction) {
    case Action::ReplacePage:
    case Action::AddPage:
        if (auto status = stream.readVarInt(mPageIndexA); !status) return status;
        if (auto status = stream.readString(mTextA); !status) return status;
        return stream.readString(mTextB);
    case Action::DeletePage:
        return stream.readVarInt(mPageIndexA);
    case Action::SwapPages:
        if (auto status = stream.readVarInt(mPageIndexA); !status) return status;
        return stream.readVarInt(mPageIndexB);
    case Action::Finalize:
        if (auto status = stream.readString(mTextA); !status) return status;
        if (auto status = stream.readString(mTextB); !status) return status;
        return stream.readString(mXuid);
    default:
        return {};
    }
}

} // namespace sculk::protocol::inline abi_v944
