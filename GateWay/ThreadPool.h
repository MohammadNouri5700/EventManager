//
// Created by aziz on 29.08.21.
//

#ifndef EVENT_MANAGER_THREADPOOL_H
#define EVENT_MANAGER_THREADPOOL_H

#include <future>

#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <thread>


class ThreadPool
{
public:
    ThreadPool(const size_t &threads= std::thread::hardware_concurrency(), const unsigned int &capacity = std::thread::hardware_concurrency());

    void Wait();
    void Join();

    void Reset();

    template <class F>
    void Post(F&& f)
    {
        Queue.wait();
        boost::asio::post(*Workers, [this, f = std::forward<F>(f)] {
            f();
            Queue.post();
        });
    }
    template <class F>
    auto Submit(F&& f) -> std::future<decltype(f())>
    {
        Queue.wait();
        std::promise<decltype(f())> promise;
        auto future = promise.get_future();
        boost::asio::post(*Workers, [this, promise = std::move(promise), f = std::forward<F>(f)] () mutable {
            promise.set_value(f());
            Queue.post();
        });
        return future;
    }

private:
    std::size_t const Threads{};
    std::unique_ptr<boost::asio::thread_pool> Workers{};
    boost::interprocess::interprocess_semaphore Queue;
};


#endif //EVENT_MANAGER_THREADPOOL_H
