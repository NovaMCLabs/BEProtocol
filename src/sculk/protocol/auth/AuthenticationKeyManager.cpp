// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/auth/AuthenticationKeyManager.hpp"
#include "../ssl/ES384.hpp"
#include "../ssl/RS256.hpp"
#include <httplib.h>
#include <random>
#include <sculk/reflection/jsonc/reflection.hpp>

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

#define SCULK_CACHED_MOJANG_PUBLIC_KEY_1                                                                               \
    rs256::jwkRsaPublicKeyToPem(                                                                                       \
        "v6h-mczOLc3EJRuvDf4EmqX6Q5aLVEtJGd-YqbG819Mb5IPdu4-IR4QjlvEBEJlyz-_"                                          \
        "tLJY4iUtneODoandNG0fuROxhwrXGFFt4Gq6kUkp0S7QavKj8jSgBkmgm0ZorTJQW5qN_"                                        \
        "tXNRlc3Ven3JWU6xHMBWLv1LVY3kOQTOxythQiwT6rkw1Kec8T0LJ4dZ1x1vGw47rvBMuy7VRC4SIPtaOcnzFBPDO2TK7oZGEZoEPVpNskn7" \
        "VmKmngSgziQQsG3NLD4AZADT8y3eq3dZYumHiI-mggnqm30yN5Jh7eBZwGJjLlWLYroHbuEen-OSh5DZO6J5E3y_MlEvfPi_EQ",          \
        "AQAB"                                                                                                         \
    )

#define SCULK_CACHED_MOJANG_PUBLIC_KEY_2                                                                               \
    rs256::jwkRsaPublicKeyToPem(                                                                                       \
        "01yUt6cmX3vfduSSYgKPEGxUrTNpWgCcWqvQY0ZO4q_"                                                                  \
        "OoWxKR83F3q5hSfVBhM7zCXPfIgwSczi4Aoe9vzqiDaT0WtTFtgxKWle2cxpUucweRWIbqjG_"                                    \
        "Xba4XWX4yf26EvhzWv65ZTTeqgGYeca1K3hon8ytOrWQMlixCfEbWnC5bDwz_nDOkj_pPXHzXGn7VZGDs7NLE2_WUsgWIt_"              \
        "lWvWmkDINmvSznCcGySg9r6DnC7Md3BxlEYWjZ-FnkFgl7yuI-0AfpJDPYt6fTU5Gfey1b_"                                      \
        "DAva88dR84r4FgzcGxR3Zp4f8uPOOBh5xmEXBybl57COEmMOZH_uRsXmRFCQ",                                                \
        "AQAB"                                                                                                         \
    )

#define SCULK_CACHED_MOJANG_PUBLIC_KEY_3                                                                               \
    rs256::jwkRsaPublicKeyToPem(                                                                                       \
        "vgK8g_3_D1g0_TW_6GLknn89L1xr7XLlEqbeFT691h2OxmlK1nfuKZBxKpVRWPjFg_zuCXX0ToZS-"                                \
        "4WZPR6yRKWrYHgcr2eqeXAhCqDqrG2YjicY69jglN8DntBHAlrvqJrq7LsJ2v4B4Vm3oprcObDCDuS1pLU5jHUuJPA4P95yQBUCfRSql7ehm" \
        "WZtgGUkalGsdgTw7w3UAwJPDQmS3ElfsJgX6_47D9o8JYnuIFjOoluLmmZ1uSOTUhZ-"                                          \
        "bq63E6I5kWIb9FQIMEr10WSwkuubciZjNiBZupib6k5iIFsl7VtjIeCsnFA1QjcgMM3mNBmLiGThbruFHG3B2iXNdQ",                  \
        "AQAB"                                                                                                         \
    )

#define SCULK_CACHED_MOJANG_PUBLIC_KEY_4                                                                               \
    rs256::jwkRsaPublicKeyToPem(                                                                                       \
        "xbkxk_g4pFw9Wp0mr43dZdVe4FnY1sKdBBgrgaCs7EfxCmFJmSxOEgh6Ih1NjdpWxMWsrAAxxDyHv_"                               \
        "a7RvEg9q2Bz3S6moVVcpPnJtP6Ixw5XLFua_gWdfEqkxE3G1rmu9WcXUYolHwRXl_0aN1nOxvkGDBYb70FMfJ-"                       \
        "PZyVh5VAY0Auch0FB7n0qs2nRW1Pa8IeIm4t_LubDfcjuRhkGR1mMH9snZUggwh_"                                             \
        "WXYybB75kZmdnQOeK7P9LXZsfwYj1eI5NsTVpHq370YAMWfHc6dfj5SG59WuAQ50KXHNReXt2bS7_"                                \
        "GIV9hlgHfeHQF7YG0R0TEOyTYuEdJ39qDlwAQ",                                                                       \
        "AQAB"                                                                                                         \
    )

AuthenticationKeyManager::AuthenticationKeyManager(std::chrono::seconds leeway) : mLeeway(leeway) {}

std::optional<std::string_view> AuthenticationKeyManager::getPublicKeyPemByKeyId(const std::string& keyId) const {
    auto it = mPublicKeysPemByKeyId.find(keyId);
    if (it != mPublicKeysPemByKeyId.end()) {
        return it->second;
    }
    return {};
}

std::string_view AuthenticationKeyManager::getExpectedIssuer() const { return mExpectedIssuer; }

std::string_view AuthenticationKeyManager::getExpectedPlayFabTitle() const { return mExpectedPlayFabTitle; }

struct MojangServiceFetchResult {
    struct {
        struct {
            struct {
                struct {
                    std::string serviceUri{};
                    std::string issuer{};
                    std::string playfabTitleId{};
                    std::string eduPlayFabTitleId{};
                } prod;
            } auth;
        } serviceEnvironments;
    } result;
};

struct MojangConfigFetchResult {
    std::string issuer{};
};

struct MojangPublicKeyFetchResult {
    struct KeyInfo {
        std::string kty{};
        std::string use{};
        std::string kid{};
        std::string x5t{};
        std::string n{};
        std::string e{};
    };
    std::vector<KeyInfo> keys{};
};

AuthenticationKeyManager& AuthenticationKeyManager::setLeeway(std::chrono::seconds leeway) {
    mLeeway = leeway;
    return *this;
}

Result<> AuthenticationKeyManager::initMojangPublicKeyFromNetwork(std::size_t timeoutSeconds) {
    // https://client.discovery.minecraft-services.net/api/v1.0/discovery/MinecraftPE/builds/1.0.0.0
    httplib::Client serviceClient("https://client.discovery.minecraft-services.net");
    serviceClient.set_connection_timeout(timeoutSeconds);
    serviceClient.set_read_timeout(timeoutSeconds);
    serviceClient.set_write_timeout(timeoutSeconds);
    httplib::Result serviceRes = serviceClient.Get("/api/v1.0/discovery/MinecraftPE/builds/1.0.0.0");
    if (!serviceRes || serviceRes->status != 200) {
        return error_utils::makeError("Failed to fetch Mojang service from Internet");
    }
    auto serviceJson = jsonc::json::parse(serviceRes->body);
    if (!serviceJson) {
        return error_utils::makeError("Failed to parse Mojang service response JSON");
    }
    MojangServiceFetchResult fetchResult{};
    if (auto status = reflection::jsonc::deserialize(fetchResult, *serviceJson); !status) {
#ifdef SCULK_PROTOCOL_ENABLE_DETAIL_ERRORS
        return error_utils::makeError(
            std::format("Failed to deserialize Mojang service response JSON: {}", status.error())
        );
#else
        return error_utils::makeError("Failed to deserialize Mojang service response JSON");
#endif
    }
    mExpectedPlayFabTitle = std::move(fetchResult.result.serviceEnvironments.auth.prod.playfabTitleId);

    httplib::Client keyClient(fetchResult.result.serviceEnvironments.auth.prod.serviceUri);
    keyClient.set_connection_timeout(timeoutSeconds);
    keyClient.set_read_timeout(timeoutSeconds);
    keyClient.set_write_timeout(timeoutSeconds);
    // {auth service base URL}/.well-known/keys
    httplib::Result keyRes = keyClient.Get("/.well-known/keys");
    if (!keyRes || keyRes->status != 200) {
        return error_utils::makeError("Failed to fetch Mojang public key from Internet");
    }
    auto keyJson = jsonc::json::parse(keyRes->body);
    if (!keyJson) {
        return error_utils::makeError("Failed to parse Mojang public key response JSON");
    }
    MojangPublicKeyFetchResult keyFetchResult{};
    if (auto status = reflection::jsonc::deserialize(keyFetchResult, *keyJson); !status) {
#ifdef SCULK_PROTOCOL_ENABLE_DETAIL_ERRORS
        return error_utils::makeError(
            std::format("Failed to deserialize Mojang public key response JSON: {}", status.error())
        );
#else
        return error_utils::makeError("Failed to deserialize Mojang public key response JSON");
#endif
    }
    if (keyFetchResult.keys.empty()) {
        return error_utils::makeError("Mojang public key response JSON does not contain any keys");
    }
    mPublicKeysPemByKeyId.clear();
    for (const auto& keyInfo : keyFetchResult.keys) {
        if (keyInfo.kty == "RSA" && keyInfo.use == "sig") {
            std::string pem{};
            if (!rs256::jwkRsaPublicKeyToPem(keyInfo.n, keyInfo.e, pem)) {
                return error_utils::makeError("Failed to convert Mojang public key from JWK to PEM format");
            }
            mPublicKeysPemByKeyId.emplace(keyInfo.kid, std::move(pem));
        }
    }

    // {auth service base URL}/.well-known/openid-configuration
    httplib::Result issuerRes = keyClient.Get("/.well-known/openid-configuration");
    if (!issuerRes || issuerRes->status != 200) {
        return error_utils::makeError("Failed to fetch Mojang configuration from Internet");
    }
    auto issuerJson = jsonc::json::parse(issuerRes->body);
    if (!issuerJson) {
        return error_utils::makeError("Failed to parse Mojang configuration response JSON");
    }
    MojangConfigFetchResult configFetchResult{};
    if (auto status = reflection::jsonc::deserialize(configFetchResult, *issuerJson); !status) {
#ifdef SCULK_PROTOCOL_ENABLE_DETAIL_ERRORS
        return error_utils::makeError(
            std::format("Failed to deserialize Mojang configuration response JSON: {}", status.error())
        );
#else
        return error_utils::makeError("Failed to deserialize Mojang configuration response JSON");
#endif
    }
    mExpectedIssuer = std::move(configFetchResult.issuer);

    return {};
}

void AuthenticationKeyManager::initMojangPublicKeyFromCachedKeys() {
    mPublicKeysPemByKeyId = {
        {"C1D78C9429FE3EC5D72000398E256C302D8A7833", SCULK_CACHED_MOJANG_PUBLIC_KEY_1},
        {"37959048C139ECD3712923EE3A05B6C3D8DAC402", SCULK_CACHED_MOJANG_PUBLIC_KEY_2},
        {"E9544A8594022198E82407994498E38E84A888FD", SCULK_CACHED_MOJANG_PUBLIC_KEY_3},
        {"6CD621632CEE45A16374B30445B1FB9B77EC7BF7", SCULK_CACHED_MOJANG_PUBLIC_KEY_4},
    };
    mExpectedIssuer       = "https://authorization.franchise.minecraft-services.net/";
    mExpectedPlayFabTitle = "20CA2";
}

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE