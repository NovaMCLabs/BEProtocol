// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/utility/deps/Result.hpp"
#include "sculk/protocol/connection/encryption/JsonWebToken.hpp"
#include <unordered_map>

namespace sculk::protocol::inline abi_v975 {

class AuthenticationKeyManager {
public:
    std::unordered_map<std::string, std::string> mRS256PublicKeys{}; // kid: PublicKeyPem

public:
    [[nodiscard]] Result<> initializeMojangPublicKeyFromInternet();

    [[nodiscard]] Result<> verifyJwt(const JsonWebToken& jwt);
};

} // namespace sculk::protocol::inline abi_v975
