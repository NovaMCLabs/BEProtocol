// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/connection/auth/LegacyCertificateChain.hpp"
#include "../../codec/utility/Reflection.hpp"

namespace sculk::protocol::inline abi_v944 {

Result<> LegacyCertificateChain::load(std::string_view certificateJson) {
    auto jsonObj = jsonc::json::parse(certificateJson);
    if (!jsonObj) {
        return error_utils::makeError("Failed to parse certificate chain JSON");
    }

    auto& jsonRef = *jsonObj;
    if (!jsonRef.contains("chain") || !jsonRef["chain"].is_array()) {
        return error_utils::makeError("Invalid certificate chain format: missing 'chain' array");
    }

    mCertificates.clear();
    for (const auto& certJson : jsonRef["chain"]) {
        if (!certJson.is_string()) {
            return error_utils::makeError("Invalid certificate chain format: expected array of strings");
        }

        LegacyCertificate cert{};
        if (auto status = cert.load(certJson.as<std::string>()); !status) {
            return error_utils::makeError("Failed to load certificate in chain");
        }

        mCertificates.push_back(std::move(cert));
    }
    return {};
}

std::string LegacyCertificateChain::saveAndSign(std::string_view eccPrivateKey) {
    jsonc::json jsonRef = jsonc::json::object();
    jsonRef["chain"]    = jsonc::json::array();
    for (auto& cert : mCertificates) {
        jsonRef["chain"].push_back(cert.saveAndSign(eccPrivateKey));
    }
    return jsonRef.dump(-1);
}

} // namespace sculk::protocol::inline abi_v944