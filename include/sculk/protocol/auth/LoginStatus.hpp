// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <cstdint>

namespace sculk::protocol::inline abi_v975 {

enum class LoginStatus : std::uint8_t {
    Mojang           = 0,
    SelfSigned       = 1,
    MojangLegacy     = 2,
    SelfSignedLegacy = 3,
};

} // namespace sculk::protocol::inline abi_v975
