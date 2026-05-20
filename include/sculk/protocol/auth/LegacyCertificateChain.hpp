// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "LegacyCertificate.hpp"
#include <vector>

namespace sculk::protocol::inline abi_v975 {

class LegacyCertificateChain {
public:
    std::vector<LegacyCertificate> mCertificates{};

public:
    [[nodiscard]] Result<> load(std::string_view certificateJson);

    [[nodiscard]] std::string saveAndSign(std::string_view eccPrivateKey);
};

} // namespace sculk::protocol::inline abi_v975