// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/auth/LegacyCertificateChain.hpp"
#include "sculk/reflection/jsonc/reflection.hpp"
#include "ssl/ES384.hpp"

namespace sculk::protocol::inline abi_v975 {

#define SCULK_CERTIFICATE_SERIALIZE_OPTION_INIT() static reflection::jsonc::options options{.indent = -1}

#define SCULK_CERTIFICATE_CREATE_JSON(PART, DATA)                                                                      \
    jsonc::json PART##Json = jsonc::json::object();                                                                    \
    const auto& PART       = DATA;

#define SCULK_CERTIFICATE_SERIALIZE(PART, FIELD)                                                                       \
    auto FIELD = reflection::jsonc::serialize<false, false>(PART.FIELD, options);                                      \
    if (!FIELD.is_null()) {                                                                                            \
        PART##Json[#FIELD] = FIELD;                                                                                    \
    }

#define SCULK_CERTIFICATE_PARSE_JSON(PART, RAW)                                                                        \
    auto PART##JsonStr = base64url::decodeChecked(RAW);                                                                \
    if (!PART##JsonStr) {                                                                                              \
        return error_utils::makeError("Failed to decode certificate " #PART);                                          \
    }                                                                                                                  \
    auto PART##JsonOpt = jsonc::json::parse(*PART##JsonStr);                                                           \
    if (!PART##JsonOpt) {                                                                                              \
        return error_utils::makeError("Failed to parse certificate " #PART " JSON");                                   \
    }                                                                                                                  \
    const auto& PART##Json = *PART##JsonOpt;

#define SCULK_CERTIFICATE_DESERIALIZE(PART, FIELD)                                                                     \
    if (!PART##Json.contains(#FIELD)) {                                                                                \
        return error_utils::makeError("Certificate JSON does not contain a valid field '" #FIELD "'");                 \
    }                                                                                                                  \
    if (!reflection::jsonc::deserialize<false, false>(PART.FIELD, PART##Json[#FIELD], options)) {                      \
        return error_utils::makeError("Failed to deserialize certificate " #PART " field '" #FIELD "'");               \
    }

bool Certificate::verify(std::string_view publicKeyPem) const {
    std::string signingInput = std::format("{}.{}", mRawHeader, mRawPayload);
    return es384::verifyES384Signature(signingInput, mSignature, publicKeyPem);
}

bool Certificate::sign(std::string_view privateKeyPem) {
    SCULK_CERTIFICATE_SERIALIZE_OPTION_INIT();

    SCULK_CERTIFICATE_CREATE_JSON(header, mHeader);
    SCULK_CERTIFICATE_SERIALIZE(header, alg);
    SCULK_CERTIFICATE_SERIALIZE(header, x5u);
    SCULK_CERTIFICATE_SERIALIZE(header, x5t);
    mRawHeader = base64url::encode(headerJson.dump());

    SCULK_CERTIFICATE_CREATE_JSON(payload, mPayload);
    SCULK_CERTIFICATE_SERIALIZE(payload, nbf);
    SCULK_CERTIFICATE_SERIALIZE(payload, exp);
    SCULK_CERTIFICATE_SERIALIZE(payload, identityPublicKey);
    SCULK_CERTIFICATE_SERIALIZE(payload, certficateAuthority);
    SCULK_CERTIFICATE_SERIALIZE(payload, randomNonce);
    SCULK_CERTIFICATE_SERIALIZE(payload, iss);
    SCULK_CERTIFICATE_SERIALIZE(payload, iat);
    SCULK_CERTIFICATE_SERIALIZE(payload, extraData);
    mRawPayload = base64url::encode(payloadJson.dump());

    std::string signingInput = std::format("{}.{}", mRawHeader, mRawPayload);
    return es384::signES384Signature(signingInput, privateKeyPem, mSignature);
}

Result<Certificate> Certificate::fromString(std::string_view certificateStr) {
    SCULK_CERTIFICATE_SERIALIZE_OPTION_INIT();

    const auto first = certificateStr.find('.');
    const auto last  = certificateStr.rfind('.');

    if (first == std::string::npos || last == std::string::npos || first == last) {
        return error_utils::makeError("Invalid certificate format: expected three parts separated by dots");
    }

    auto   rawHeader = certificateStr.substr(0, first);
    Header header{};
    SCULK_CERTIFICATE_PARSE_JSON(header, rawHeader);
    SCULK_CERTIFICATE_DESERIALIZE(header, alg);
    if (header.alg != "ES384") {
        return error_utils::makeError("certificate signing algorithm must be ES384");
    }
    SCULK_CERTIFICATE_DESERIALIZE(header, x5u);
    SCULK_CERTIFICATE_DESERIALIZE(header, x5t);

    auto    rawPayload = certificateStr.substr(first + 1, last - first - 1);
    Payload payload{};
    SCULK_CERTIFICATE_PARSE_JSON(payload, rawPayload);
    SCULK_CERTIFICATE_DESERIALIZE(payload, nbf);
    SCULK_CERTIFICATE_DESERIALIZE(payload, exp);
    SCULK_CERTIFICATE_DESERIALIZE(payload, identityPublicKey);
    SCULK_CERTIFICATE_DESERIALIZE(payload, certficateAuthority);
    SCULK_CERTIFICATE_DESERIALIZE(payload, randomNonce);
    SCULK_CERTIFICATE_DESERIALIZE(payload, iss);
    SCULK_CERTIFICATE_DESERIALIZE(payload, iat);
    SCULK_CERTIFICATE_DESERIALIZE(payload, extraData);

    auto signature = certificateStr.substr(last + 1);

    return Certificate{
        .mRawHeader  = std::string(rawHeader),
        .mHeader     = std::move(header),
        .mRawPayload = std::string(rawPayload),
        .mPayload    = std::move(payload),
        .mSignature  = std::string(signature)
    };
}


std::string LegacyCertificateChain::toString() const {
    jsonc::json certChainJson = {
        {"chain", jsonc::json::array({})}
    };
    if (mClientCertificate) {
        certChainJson["chain"].push_back(mClientCertificate->toString());
    }
    if (mMojangCertificate) {
        certChainJson["chain"].push_back(mMojangCertificate->toString());
    }
    certChainJson["chain"].push_back(mLoginCertificate.toString());
    return certChainJson.dump();
}

bool LegacyCertificateChain::verify(std::string_view publicKeyPem) const {
    (void)publicKeyPem;
    // TODO: Implement actual verification logic
    return true;
}

Result<LegacyCertificateChain> LegacyCertificateChain::fromString(std::string_view certificateChainJsonStr) {
    auto certJsonOpt = jsonc::json::parse(certificateChainJsonStr);
    if (!certJsonOpt) {
        return error_utils::makeError("Failed to parse certificate chain JSON");
    }

    const auto& certJson = *certJsonOpt;
    if (!certJson.contains("chain") || !certJson["chain"].is_array()) {
        return error_utils::makeError("Certificate JSON does not contain a valid 'chain' field");
    }

    std::size_t certCount = certJson["chain"].size();
    if (certCount == 1) {
        // TODO: offline mode, only login certificate is present
    } else if (certCount == 3) {
        // TODO: online mode, client and login certificates are present
    } else {
        return error_utils::makeError("Certificate JSON 'chain' field must contain either 1 or 3 certificates");
    }

    // TODO: Implement actual parsing logic to populate the LegacyCertificateChain object based on the JSON structure

    return LegacyCertificateChain{};
}

} // namespace sculk::protocol::inline abi_v975
