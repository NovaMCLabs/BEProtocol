// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/Version.hpp"
#include "sculk/protocol/connection/thread/ThreadPool.hpp"
#include <atomic>
#include <concepts>
#include <concurrentqueue.h>
#include <cstdint>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE::thread {

class TaskStrand final {
public:
#ifndef _LIBCPP_VERSION
    using Task = std::move_only_function<void()>;
#else
    class Task final {
    private:
        struct Concept {
            virtual ~Concept()           = default;
            virtual void call() noexcept = 0;
        };

        template <typename F>
        struct Model final : Concept {
            F mFunction;

            explicit Model(F&& function) noexcept(std::is_nothrow_move_constructible_v<F>)
            : mFunction(std::move(function)) {}

            void call() noexcept override { std::invoke(mFunction); }
        };

    public:
        Task() = default;

        template <typename F>
            requires std::invocable<F&>
        explicit Task(F&& function) : mFunction(std::make_unique<Model<std::decay_t<F>>>(std::forward<F>(function))) {}

        Task(const Task&)            = delete;
        Task& operator=(const Task&) = delete;

        Task(Task&&) noexcept            = default;
        Task& operator=(Task&&) noexcept = default;

        explicit operator bool() const noexcept { return static_cast<bool>(mFunction); }

        void operator()() noexcept { mFunction->call(); }

    private:
        std::unique_ptr<Concept> mFunction{};
    };
#endif

    static constexpr std::uint32_t DEFAULT_MAX_PENDING_TASKS = 2048;

public:
    explicit TaskStrand(
        ThreadPool*   threadPool      = nullptr,
        std::uint32_t maxPendingTasks = DEFAULT_MAX_PENDING_TASKS
    ) noexcept
    : mThreadPool(threadPool),
      mMaxPendingTasks(maxPendingTasks) {}

    void setThreadPool(ThreadPool* threadPool) noexcept { mThreadPool = threadPool; }

    void setMaxPendingTasks(std::uint32_t maxPendingTasks) noexcept {
        mMaxPendingTasks.store(maxPendingTasks, std::memory_order_release);
    }

    [[nodiscard]] std::uint32_t maxPendingTasks() const noexcept {
        return mMaxPendingTasks.load(std::memory_order_acquire);
    }

    template <typename F>
        requires std::invocable<F&>
    [[nodiscard]] bool enqueue(F&& task) noexcept {
        Task wrapped{std::forward<F>(task)};
        if (!wrapped) {
            return false;
        }

        auto pending = mPendingTasks.fetch_add(1, std::memory_order_acq_rel) + 1;
        if (pending > mMaxPendingTasks.load(std::memory_order_acquire)) {
            mPendingTasks.fetch_sub(1, std::memory_order_acq_rel);
            mDroppedCount.fetch_add(1, std::memory_order_relaxed);
            return false;
        }

        auto* pool = mThreadPool;
        if (!pool) {
            mPendingTasks.fetch_sub(1, std::memory_order_acq_rel);
            mDroppedCount.fetch_add(1, std::memory_order_relaxed);
            return false;
        }

        if (!mTasks.enqueue(std::move(wrapped))) {
            mPendingTasks.fetch_sub(1, std::memory_order_acq_rel);
            mDroppedCount.fetch_add(1, std::memory_order_relaxed);
            return false;
        }

        scheduleDrain(*pool);
        return true;
    }

    [[nodiscard]] std::uint64_t droppedCount() const noexcept { return mDroppedCount.load(std::memory_order_relaxed); }

    [[nodiscard]] std::uint32_t pendingTasks() const noexcept { return mPendingTasks.load(std::memory_order_acquire); }

private:
    void scheduleDrain(ThreadPool& pool) noexcept {
        if (mDrainScheduled.exchange(true, std::memory_order_acq_rel)) {
            return;
        }

        const bool submitted = pool.submit([this]() noexcept { drain(); });
        if (!submitted) {
            mDrainScheduled.store(false, std::memory_order_release);
            mDroppedCount.fetch_add(1, std::memory_order_relaxed);
        }
    }

    void drain() noexcept {
        Task task;

        for (;;) {
            while (mTasks.try_dequeue(task)) {
                task();
                task = Task{};
                mPendingTasks.fetch_sub(1, std::memory_order_acq_rel);
            }

            mDrainScheduled.store(false, std::memory_order_release);

            if (!mTasks.try_dequeue(task)) {
                break;
            }

            if (mDrainScheduled.exchange(true, std::memory_order_acq_rel)) {
                (void)mTasks.enqueue(std::move(task));
                break;
            }

            task();
            task = Task{};
            mPendingTasks.fetch_sub(1, std::memory_order_acq_rel);
        }
    }

private:
    ThreadPool*                       mThreadPool{nullptr};
    moodycamel::ConcurrentQueue<Task> mTasks{};
    std::atomic_uint32_t              mMaxPendingTasks{DEFAULT_MAX_PENDING_TASKS};
    std::atomic_uint32_t              mPendingTasks{0};
    std::atomic_bool                  mDrainScheduled{false};
    std::atomic<std::uint64_t>        mDroppedCount{0};
};

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE::thread
