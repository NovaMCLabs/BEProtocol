// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/connection/encryption/JsonWebToken.hpp"
#include <unordered_map>

namespace sculk::protocol::inline abi_v975 {

class LoginToken : public JsonWebToken {
public:
    struct TokenPayload {
        std::string mid{};
        std::string xuid{};
        std::string xname{};
        std::string cpk{};
    };

public:
    TokenPayload mTokenPayload{};

public:
    [[nodiscard]] Result<> load(std::string_view compactJwt);

    [[nodiscard]] std::string saveAndSign(std::string_view rsaPrivateKey);
};

} // namespace sculk::protocol::inline abi_v975