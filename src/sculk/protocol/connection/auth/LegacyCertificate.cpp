// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/connection/auth/LegacyCertificate.hpp"
#include "../../codec/utility/Reflection.hpp"
#include "sculk/protocol/connection/encryption/Base64Url.hpp"

namespace sculk::protocol::inline abi_v975 {

Result<> LegacyCertificate::load(std::string_view compactJwt) {
    const auto first = compactJwt.find('.');
    const auto last  = compactJwt.rfind('.');
    if (first == std::string::npos || last == std::string::npos || first == last) {
        return error_utils::makeError("Invalid JWT format: expected three segments separated by dots");
    }

    mRawHeader = compactJwt.substr(0, first);
    if (auto status = utils::deserialize_json(mHeader, base64url::decode(mRawHeader)); !status) {
        return error_utils::makeError("Failed to deserialize JWT header");
    }
    if (mHeader.alg != JsonWebToken::Algorithm::ES384) {
        return error_utils::makeError("Invalid JWT Alogorithm: expected ES384 for LegacyCertificate");
    }

    mRawPayload      = compactJwt.substr(first + 1, last - first - 1);
    auto payloadJson = jsonc::json::parse(base64url::decode(mRawPayload));
    if (!payloadJson) {
        return error_utils::makeError("Failed to parse JWT payload as JSON");
    }

    if (auto status = utils::deserialize_from_json(mPayload, *payloadJson); !status) {
        return error_utils::makeError("Failed to deserialize JWT payload");
    }
    if (auto status = utils::deserialize_from_json(mCertificatePayload, *payloadJson); !status) {
        return error_utils::makeError("Failed to deserialize JWT payload into CertificatePayload");
    }

    mSignature = base64url::decode(compactJwt.substr(last + 1));
    if (mSignature.size() != 96) {
        return error_utils::makeError("Invalid JWT signature length: expected 96 bytes for ES384 signature");
    }

    return Result<>{};
}

std::string LegacyCertificate::saveAndSign(std::string_view eccPrivateKey) {
    mRawHeader       = base64url::encode(utils::serialize_json(mHeader));
    auto payloadJson = utils::serialize_to_json(mCertificatePayload);
    payloadJson.merge_patch(utils::serialize_to_json(mPayload));
    mRawPayload = base64url::encode(payloadJson.dump(-1));
    return signES384(eccPrivateKey);
}

} // namespace sculk::protocol::inline abi_v975