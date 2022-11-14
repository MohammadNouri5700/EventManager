//
// Created by aziz on 17.10.21.
//

#ifndef EVENT_MANAGER_COAPNODE_H
#define EVENT_MANAGER_COAPNODE_H
#include "Coap.h"
#include "Server.h"
#include "client.h"


namespace CoAP
{
class CoapNode
{
    std::vector<Coap *> NodeS;
public:
    virtual void Run();
    virtual ~CoapNode(){}
};
}

#endif //EVENT_MANAGER_COAPNODE_H
