// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/connection/BatchedPackets.hpp"
#include "compression/Snappy.hpp"
#include "compression/Zlib.hpp"
#include "sculk/protocol/codec/MinecraftPackets.hpp"
#include "sculk/protocol/utility/BinaryStream.hpp"
#include "sculk/protocol/utility/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v975 {

std::vector<std::byte> BatchedPackets::serialize() const {
    std::vector<std::byte> data{};
    BinaryStream           stream{data};
    for (const auto& packet : mPackets) {
        BinaryStream packetStream{data};
        packet->writeWithHeader(packetStream);
        stream.writeUnsignedVarInt(static_cast<std::uint32_t>(packetStream.size()));
        stream.writeBytes(packetStream.data(), packetStream.size());
    }
    return data;
}

Result<> BatchedPackets::deserialize(const std::vector<std::byte>& data) {
    ReadOnlyBinaryStream stream{data};
    while (stream.hasDataLeft()) {
        std::uint32_t packetLength{};

        if (!stream.readUnsignedVarInt(packetLength)) {
#ifdef SCULK_PROTOCOL_ENABLE_DETAIL_ERRORS
            return error_utils::makeError(
                std::format(
                    "Failed to read packet length: read overflowed, mReadPointer={}, size={}",
                    stream.getPosition(),
                    stream.size()
                )
            );
#else
            return error_utils::makeError("Failed to read packet length: read overflowed");
#endif
        }

        auto expectedReadPointor = stream.getPosition() + packetLength;
        if (expectedReadPointor > stream.size()) {
#ifdef SCULK_PROTOCOL_ENABLE_DETAIL_ERRORS
            return error_utils::makeError(
                std::format(
                    "Failed to read packet data: packet length exceeds remaining data, packetLength={}, "
                    "mReadPointer={}, size={}",
                    packetLength,
                    stream.getPosition(),
                    stream.size()
                )
            );
#else
            return error_utils::makeError("Failed to read packet data: packet length exceeds remaining data");
#endif
        }

        auto packet = MinecraftPackets::readAndCreatePacketFromStream(stream);
        if (!packet) {
#ifdef SCULK_PROTOCOL_ENABLE_DETAIL_ERRORS
            return error_utils::makeError(
                std::format(
                    "Failed to read packet from stream: packet data is invalid, mReadPointer={}, size={}",
                    stream.getPosition(),
                    stream.size()
                )
            );
#else
            return error_utils::makeError("Failed to read packet from stream: packet data is invalid");
#endif
        }

        if (stream.getPosition() != expectedReadPointor) {
#ifdef SCULK_PROTOCOL_ENABLE_DETAIL_ERRORS
            return error_utils::makeError(
                std::format(
                    "Packet length mismatch: expected to read until {}, but read pointer is at {}, size={}",
                    expectedReadPointor,
                    stream.getPosition(),
                    stream.size()
                )
            );
#else
            return error_utils::makeError("Packet length mismatch");
#endif
        }

        mPackets.push_back(std::move(packet));
    }
    return {};
}

} // namespace sculk::protocol::inline abi_v975