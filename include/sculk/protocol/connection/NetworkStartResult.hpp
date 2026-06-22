// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/Version.hpp"
#include <cstdint>

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

enum class NetworkStartResult : std::uint8_t {
    Success                     = 0,
    AlreadyStarted              = 1,
    InvalidSocketDescriptors    = 2,
    InvalidMaxConnections       = 3,
    SocketFamilyNotSupported    = 4,
    SocketPortAlreadyInUse      = 5,
    SocketFailedToBind          = 6,
    SocketFailedTestSend        = 7,
    PortCannotBeZero            = 8,
    FailedToCreateNetworkThread = 9,
    CouldNotGenerateGuid        = 10,
    UnknownError                = 11,
};

}