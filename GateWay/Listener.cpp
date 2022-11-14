//
// Created by aziz on 03.08.21.
//
#include "Listener.h"

GateWay::LISTENer::Listener::Listener() {}

GateWay::LISTENer::Listener::~Listener()
{

}

void GateWay::LISTENer::Listener::SetNodes(ProtocolS::Protocol *pNode)
{
    std::thread t{std::bind(&ProtocolS::Protocol::Listen, pNode)};
    aNodes.push_back(std::move(t));
}

void GateWay::LISTENer::Listener::ListenLoop()
{
    for (std::thread & th: aNodes) {
        if (th.joinable())
            th.join();
    }
}
