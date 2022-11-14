//
// Created by aziz on 23.08.21.
//

#ifndef EVENT_MANAGER_MASTER_H
#define EVENT_MANAGER_MASTER_H
#include "ModBus.h"
#include <functional>
#include <atomic>
namespace ModBUS
{
using mHandlerAct = std::function <bool()>;

class Master: public ModBus<Modbus::Master>
{
protected:
    mHandlerAct  ActCb{};
    int iSlaveID{10};
    std::atomic_bool bStopThread{false};
public:
    Master();
    ~Master();
    void Run();
    void SetAct(mHandlerAct & cb)
    {
        ActCb = cb;
    };

    void Stop();
};
}


#endif //EVENT_MANAGER_MASTER_H
