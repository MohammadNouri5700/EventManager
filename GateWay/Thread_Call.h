//
// Created by aziz on 07.09.21.
//

#ifndef EVENT_MANAGER_THREAD_CALL_H
#define EVENT_MANAGER_THREAD_CALL_H

#include <boost/asio.hpp>

#include <boost/bind/bind.hpp>
#include <boost/make_shared.hpp>

#include <iostream>
#include <chrono>
#include <functional>
#include <vector>
#include <map>

using namespace std::chrono_literals;

using TimerType = boost::shared_ptr<boost::asio::deadline_timer>;//= boost::make_shared<TimerType::element_type>(_io)
using ClockType = std::chrono::high_resolution_clock;
using Callback = std::function<void()>;
using boost::system::error_code;



struct IntervalTimer {
    IntervalTimer(boost::asio::io_context& io, ClockType::duration i, Callback cb);
    IntervalTimer()=delete;
    void Stop()
    {
        bRun= false;
    }
private:
    void Run();
    ClockType::duration const Interval;
    Callback CallBack;
    boost::asio::high_resolution_timer Timer;
    bool bRun{true};
};



class Thread_Call
{
private:
    boost::asio::io_context _io{};
    std::map<std::string, IntervalTimer*> v{};
public:
    void push_task(std::string name, ClockType::duration i, Callback cb);
    void run()
    {
        _io.run();
    }
    void stop(std::string n)
    {
        v[n]->Stop();
    }

};

#endif //EVENT_MANAGER_THREAD_CALL_H
