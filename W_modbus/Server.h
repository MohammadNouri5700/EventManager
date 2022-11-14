//
// Created by aziz on 23.08.21.
//

#ifndef EVENT_MANAGER_SERVER_H
#define EVENT_MANAGER_SERVER_H
#include "ModBus.h"
#include <functional>

namespace ModBUS
{
using HandlerServer = std::function<bool(Modbus::Server&)>;
class Server :public ModBus<Modbus::Server>
{
protected:
    HandlerServer ActCb{};
public:
    Server();
    ~Server();
    virtual void Run();
    void SetAct(HandlerServer& cb)
    {
        ActCb = cb;
    };

};
}


#endif //EVENT_MANAGER_SERVER_H
