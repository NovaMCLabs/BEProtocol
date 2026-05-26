// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/connection/BatchedPackets.hpp"
#include "compression/Snappy.hpp"
#include "compression/Zlib.hpp"
#include "sculk/protocol/utility/BinaryStream.hpp"
#include "sculk/protocol/utility/ReadOnlyBinaryStream.hpp"

namespace sculk::protocol::inline abi_v975 {

std::vector<std::byte> BatchedPackets::serialize () const {
    std::vector<std::byte> data{};
    BinaryStream           stream{data};
    // TODO
    return data;
}

Result<> BatchedPackets::deserialize(const std::vector<std::byte>& data) {
    ReadOnlyBinaryStream stream{data};
    // TODO
    return {};
}

} // namespace sculk::protocol::inline abi_v975