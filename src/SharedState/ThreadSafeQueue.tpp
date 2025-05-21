#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
void ThreadSafeQueue<T>::stop()
{
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _stopped = true;
    }
    _cv.notify_all();
}

template <typename T>
void ThreadSafeQueue<T>::push(const T& value)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push(value);
    _cv.notify_one();
}

template <typename T>
void ThreadSafeQueue<T>::push(T&& value)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push(std::move(value));
    _cv.notify_one();
}

template <typename T>
std::optional<T> ThreadSafeQueue<T>::wait_and_pop()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _cv.wait(lock, [&]{ return !_queue.empty() || _stopped; });
    if (_stopped) return std::nullopt;
    T value = std::move(_queue.front());
    _queue.pop();
    return value;
}

template <typename T>
std::optional<T> ThreadSafeQueue<T>::try_pop()
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_queue.empty()) return std::nullopt;
    T value = std::move(_queue.front());
    _queue.pop();
    return value;
}

template <typename T>
bool ThreadSafeQueue<T>::empty() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.empty();
}
