//
// Created by aziz on 16.08.21.
//

#ifndef W_COAP_COAP_H
#define W_COAP_COAP_H
#include <coap3/coap.h>
#include <string>
#include <vector>
#include "Pdu.h"
#include "Context.h"
namespace CoAP
{

class Coap
{
protected:

    coap_address_t Destination;
    std::string strHost{"localhost"};
    std::string strService{"5683"};
    coap_proto_t Protocol{COAP_PROTO_UDP};
    Context ctx;

    void Start();
    virtual void Init();
    virtual void Act()=0;

    int ResolveAddress();
    virtual void Process() = 0;
public:
    Coap(std::string h, std::string s): Destination{}, strHost{h}, strService{s}, ctx{} {};
    Coap();
    virtual ~Coap();
    void Run();
    virtual void End();
    void SetAddress(std::string h="localhost", std::string s="5683");
    void SetProtocol(coap_proto_t proto=COAP_PROTO_UDP)
    {
        Protocol = proto;
    }


};
}

#endif //W_COAP_COAP_H
