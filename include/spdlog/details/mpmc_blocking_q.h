<<<<<<< HEAD
// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

// multi producer-multi consumer blocking queue.
// enqueue(..) - will block until room found to put the new message.
// enqueue_nowait(..) - will return immediately with false if no room left in
// the queue.
// dequeue_for(..) - will block until the queue is not empty or timeout have
// passed.

#include <spdlog/details/circular_q.h>

#include <condition_variable>
#include <mutex>
=======
#pragma once

//
// Copyright(c) 2018 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

// async log helper :
// multi producer-multi consumer blocking queue
// enqueue(..) - will block until room found to put the new message
// enqueue_nowait(..) - will return immediatly with false if no room left in the queue
// dequeue_for(..) - will block until the queue is not empty or timeout passed

#include <condition_variable>
#include <mutex>
#include <queue>
>>>>>>> dea6bb1085466370ed6d629b4d462f299db75958

namespace spdlog {
namespace details {

template<typename T>
<<<<<<< HEAD
class mpmc_blocking_queue
{
public:
    using item_type = T;
    explicit mpmc_blocking_queue(size_t max_items)
        : q_(max_items)
    {}

#ifndef __MINGW32__
=======
class mpmc_bounded_queue
{
public:
    using item_type = T;
    explicit mpmc_bounded_queue(size_t max_items)
        : max_items_(max_items)
    {
    }

>>>>>>> dea6bb1085466370ed6d629b4d462f299db75958
    // try to enqueue and block if no room left
    void enqueue(T &&item)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
<<<<<<< HEAD
            pop_cv_.wait(lock, [this] { return !this->q_.full(); });
            q_.push_back(std::move(item));
=======
            pop_cv_.wait(lock, [this] { return this->q_.size() < this->max_items_; });
            q_.push(std::move(item));
>>>>>>> dea6bb1085466370ed6d629b4d462f299db75958
        }
        push_cv_.notify_one();
    }

<<<<<<< HEAD
    // enqueue immediately. overrun oldest message in the queue if no room left.
    void enqueue_nowait(T &&item)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            q_.push_back(std::move(item));
        }
        push_cv_.notify_one();
    }

    // try to dequeue item. if no item found. wait up to timeout and try again
    // Return true, if succeeded dequeue item, false otherwise
    bool dequeue_for(T &popped_item, std::chrono::milliseconds wait_duration)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            if (!push_cv_.wait_for(lock, wait_duration, [this] { return !this->q_.empty(); }))
            {
                return false;
            }
            popped_item = std::move(q_.front());
            q_.pop_front();
        }
        pop_cv_.notify_one();
        return true;
    }

#else
    // apparently mingw deadlocks if the mutex is released before cv.notify_one(),
    // so release the mutex at the very end each function.

    // try to enqueue and block if no room left
    void enqueue(T &&item)
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        pop_cv_.wait(lock, [this] { return !this->q_.full(); });
        q_.push_back(std::move(item));
        push_cv_.notify_one();
    }

    // enqueue immediately. overrun oldest message in the queue if no room left.
    void enqueue_nowait(T &&item)
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        q_.push_back(std::move(item));
        push_cv_.notify_one();
    }

    // try to dequeue item. if no item found. wait up to timeout and try again
    // Return true, if succeeded dequeue item, false otherwise
    bool dequeue_for(T &popped_item, std::chrono::milliseconds wait_duration)
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        if (!push_cv_.wait_for(lock, wait_duration, [this] { return !this->q_.empty(); }))
        {
            return false;
        }
        popped_item = std::move(q_.front());
        q_.pop_front();
=======
    // try to enqueue and return immdeialty false if no room left
    bool enqueue_nowait(T &&item)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            if (q_.size() == this->max_items_)
            {
                return false;
            }
            q_.push(std::forward<T>(item));
        }
        push_cv_.notify_one();
        return true;
    }

    // try to dequeue item. if no item found. wait upto timeout and try again
    // Return true, if succeeded dequeue item, false otherwise
    bool dequeue_for(T &popped_item, std::chrono::milliseconds wait_duration)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            if (!push_cv_.wait_for(lock, wait_duration, [this] { return this->q_.size() > 0; }))
            {
                return false;
            }

            popped_item = std::move(q_.front());
            q_.pop();
        }
>>>>>>> dea6bb1085466370ed6d629b4d462f299db75958
        pop_cv_.notify_one();
        return true;
    }

<<<<<<< HEAD
#endif

    size_t overrun_counter()
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        return q_.overrun_counter();
    }

    size_t size()
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        return q_.size();
    }

    void reset_overrun_counter()
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        q_.reset_overrun_counter();
    }

private:
    std::mutex queue_mutex_;
    std::condition_variable push_cv_;
    std::condition_variable pop_cv_;
    spdlog::details::circular_q<T> q_;
=======
private:
    size_t max_items_;
    std::mutex queue_mutex_;
    std::condition_variable push_cv_;
    std::condition_variable pop_cv_;

    std::queue<T> q_;
>>>>>>> dea6bb1085466370ed6d629b4d462f299db75958
};
} // namespace details
} // namespace spdlog
