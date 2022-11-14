//
// Created by aziz on 07.09.21.
//

#include "Thread_Call.h"
IntervalTimer::IntervalTimer(boost::asio::io_context &io, ClockType::duration i, Callback cb)
    : Interval(i), CallBack(cb), Timer(io)
{
    Run();
}

void IntervalTimer::Run()
{
    if (bRun) {
        Timer.expires_from_now(Interval);
        Timer.async_wait([this](error_code ErrCode) {
            if (!ErrCode) {
                CallBack();
                Run();
            }
        });
    }

}


void Thread_Call::push_task(std::string name, ClockType::duration i, Callback cb)
{
    {
        v[name]=new IntervalTimer {_io, i, std::move(cb)};
    }
}