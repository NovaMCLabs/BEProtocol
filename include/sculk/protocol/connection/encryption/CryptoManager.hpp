// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>

struct evp_cipher_ctx_st;

namespace sculk::protocol::inline abi_v944 {

struct EvpCipherCtxDeleter {
    void operator()(evp_cipher_ctx_st* ctx) const noexcept;
};

using EvpCipherCtxPtr = std::unique_ptr<evp_cipher_ctx_st, EvpCipherCtxDeleter>;

class CryptoManager {
public:
    CryptoManager() = default;
    explicit CryptoManager(std::vector<std::byte> keyBytes);

    [[nodiscard]] bool isEnabled() const;
    void               setEnabled(bool enabled);
    void               setKeyBytes(std::vector<std::byte> keyBytes);

    std::vector<std::byte> encrypt(const std::vector<std::byte>& bytes);
    std::vector<std::byte> decrypt(const std::vector<std::byte>& bytes);
    bool                   verify(const std::vector<std::byte>& bytes);

private:
    static constexpr std::size_t CHECKSUM_SIZE  = 8;
    static constexpr std::size_t AES_BLOCK_SIZE = 16;

    bool                                  mEnabled{};
    std::uint64_t                         mEncryptCounter{};
    std::uint64_t                         mDecryptCounter{};
    std::vector<std::byte>                mKeyBytes{};
    std::array<std::byte, AES_BLOCK_SIZE> mInitialCounterBlock{};
    EvpCipherCtxPtr                       mEncryptCtx{};
    EvpCipherCtxPtr                       mDecryptCtx{};
    mutable std::mutex                    mMutex{};

    [[nodiscard]] std::array<std::byte, CHECKSUM_SIZE>
    checksum(std::uint64_t counter, const std::byte* data, std::size_t dataSize) const;

    [[nodiscard]] bool                   verifyUnlocked(const std::vector<std::byte>& bytes);
    [[nodiscard]] bool                   initializeCipher(EvpCipherCtxPtr& ctx, bool encrypt) const;
    [[nodiscard]] std::vector<std::byte> ctrCrypt(EvpCipherCtxPtr& ctx, const std::vector<std::byte>& bytes) const;
};

} // namespace sculk::protocol::inline abi_v944