//
// Created by aziz on 03.08.21.
//

#ifndef EVENT_MANAGER_LISTENER_H
#define EVENT_MANAGER_LISTENER_H
#include "../Protocols/Protocol.h"
#include <thread>
#include <functional>
#include <vector>

namespace GateWay::LISTENer
{
class Listener
{
public:
    Listener();
    virtual ~Listener();
    void ListenLoop();
    void SetNodes(ProtocolS::Protocol *node);
private:
    std::vector<std::thread> aNodes{};
};
}


#endif //EVENT_MANAGER_LISTENER_H
