//
// Created by aziz on 29.08.21.
//

#include "ThreadPool.h"
ThreadPool::ThreadPool(const size_t &threads, const unsigned int &capacity)
    : Threads(threads), Queue(capacity)
{
    Reset();
}

void ThreadPool::Join()
{
    Workers->join();
}

void ThreadPool::Wait()
{
    Workers->join();
}

void ThreadPool::Reset()
{
    if (Workers) {
        Wait();
        Workers.reset();
    }
    Workers = std::make_unique<boost::asio::thread_pool>(Threads);
}
