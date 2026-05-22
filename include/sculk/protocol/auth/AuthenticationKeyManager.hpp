// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "AuthenticationType.hpp"
#include "sculk/protocol/utility/Result.hpp"
#include <chrono>
#include <optional>
#include <string>

namespace sculk::protocol::inline abi_v975 {

class AuthenticationKeyManager {
    AuthenticationType                                   mAuthenticationType{};
    std::string                                          mLegacyCertificateChainPublicKeyPem{};
    std::string                                          mLegacyCertificateChainPrivateKeyPem{};
    std::chrono::seconds                                 mValidityLeeway{60};
    std::optional<std::chrono::system_clock::time_point> mValidityTime{};

public:
    [[nodiscard]] constexpr AuthenticationType getAuthenticationType() const { return mAuthenticationType; }

    [[nodiscard]] constexpr std::chrono::seconds getValidityLeeway() const { return mValidityLeeway; }

    std::chrono::system_clock::time_point getValidityTime() const {
        return mValidityTime.value_or(std::chrono::system_clock::now());
    }

    [[nodiscard]] constexpr std::string_view getLegacyCertificateChainPublicKeyPem() const {
        return mLegacyCertificateChainPublicKeyPem;
    }

    [[nodiscard]] constexpr std::string_view getLegacyCertificateChainPrivateKeyPem() const {
        return mLegacyCertificateChainPrivateKeyPem;
    }

public:
    constexpr void setAuthenticationType(AuthenticationType authType) { mAuthenticationType = authType; }

    constexpr void setValidityLeeway(std::chrono::seconds leeway) { mValidityLeeway = leeway; }

    constexpr void setValidityTime(std::chrono::system_clock::time_point validityTime) { mValidityTime = validityTime; }

    constexpr void
    setLegacyCertificateChainPublicKeyPemPair(std::string_view publicKeyPem, std::string_view privateKeyPem) {
        mLegacyCertificateChainPublicKeyPem  = publicKeyPem;
        mLegacyCertificateChainPrivateKeyPem = privateKeyPem;
    }

    Result<> initMojangPublicKey();
};

} // namespace sculk::protocol::inline abi_v975