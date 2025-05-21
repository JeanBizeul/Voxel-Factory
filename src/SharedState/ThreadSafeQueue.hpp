#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
class ThreadSafeQueue {
 public:
    ThreadSafeQueue() = default;
    ~ThreadSafeQueue() = default;

    void push(const T& value);
    void push(T&& value);

    std::optional<T> wait_and_pop();
    std::optional<T> try_pop();

    void stop();

    bool empty() const;

 private:
    mutable std::mutex _mutex;
    std::queue<T> _queue;
    std::condition_variable _cv;

    bool _stopped = false;
};

#include "ThreadSafeQueue.tpp"
