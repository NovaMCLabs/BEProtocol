// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <cstdint>
#include <optional>

namespace sculk::protocol::inline abi_v944 {

enum class GraphicsMode : std::uint8_t {
    Simple    = 0,
    Fancy     = 1,
    Advanced  = 2,
    RayTraced = 3,
};

struct SyncedClientOptionsUpdate {
    std::optional<GraphicsMode> mGraphicsMode{};
};

} // namespace sculk::protocol::inline abi_v944
