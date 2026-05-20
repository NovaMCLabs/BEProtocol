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

class LegacyCertificate : public JsonWebToken {
public:
    struct CertificatePayload {
        std::string                                                 identityPublicKey{};
        std::optional<bool>                                         certificateAuthority{};
        std::optional<std::int64_t>                                 randomNonce{};
        std::optional<std::unordered_map<std::string, std::string>> extraData{};
    };

public:
    CertificatePayload mCertificatePayload{};

public:
    [[nodiscard]] Result<> load(std::string_view compactJwt);

    [[nodiscard]] std::string saveAndSign(std::string_view eccPrivateKey);
};

} // namespace sculk::protocol::inline abi_v975