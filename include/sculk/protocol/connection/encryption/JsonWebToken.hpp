// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/utility/deps/Result.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace sculk::protocol::inline abi_v944 {

class JsonWebToken {
public:
    enum class Algorithm {
        ES384 = 0,
        RS256 = 1,
    };

    struct Header {
        Algorithm                  alg{}; // alg: Signing algorithm (e.g. ES384, RS256)
        std::optional<std::string> x5u{}; // x5u: X.509 URL
        std::optional<std::string> x5t{}; // x5t: X.509 certificate SHA-1 thumbprint
    };

    struct Payload {
        std::optional<std::string>   iss{}; // iss: Issuer
        std::optional<std::string>   sub{}; // sub: Subject (typically a user/account identifier)
        std::optional<std::string>   aud{}; // aud: Audience (Minecraft only used single string)
        std::optional<std::uint64_t> exp{}; // exp: Expiration time (Unix timestamp, seconds)
        std::optional<std::uint64_t> nbf{}; // nbf: Not before time (Unix timestamp, seconds)
        std::optional<std::uint64_t> iat{}; // iat: Issued-at time (Unix timestamp, seconds)
        std::optional<std::string>   jti{}; // jti: JWT ID (unique token identifier, often used for anti-replay)
    };

public:
    std::string mRawHeader{};  // Base64Url-encoded JWT header segment
    Header      mHeader{};     // Decoded/deserialized header object
    std::string mRawPayload{}; // Base64Url-encoded JWT payload segment
    Payload     mPayload{};    // Decoded/deserialized payload object
    std::string mSignature{};  // Decoded signature bytes (not Base64Url text)

public:
    [[nodiscard]] Algorithm getAlgorithm() const;

    [[nodiscard]] bool verifyES384(std::string_view ecPublicKeyPem) const;

    [[nodiscard]] bool verifyRS256(std::string_view rsaPublicKeyPem) const;

    [[nodiscard]] bool verify(std::string_view publicKeyPem) const;

    [[nodiscard]] std::string signES384(std::string_view eccPrivateKeyPem);

    [[nodiscard]] std::string signRS256(std::string_view rsaPrivateKeyPem);
};

} // namespace sculk::protocol::inline abi_v944
