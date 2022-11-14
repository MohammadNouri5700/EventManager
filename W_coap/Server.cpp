//
// Created by aziz on 16.08.21.
//

#include "Server.h"

#include <iostream>

CoAP::Server::Server(): Handler(NULL)
{
}

CoAP::Server::~Server()
{
}

void CoAP::Server::Init()
{

    Coap::Init();
    if (!(pEndPoint = coap_new_endpoint(ctx.pGet(), &Destination, Protocol))) {
        coap_log(LOG_EMERG, "cannot initialize Context(aServer)\n");
        End();
    }
    if (!(pEndPoint = coap_new_endpoint(ctx.pGet(), &Destination, Protocol))) {
        coap_log(LOG_EMERG, "cannot initialize Context(aServer)\n");
        End();
    }


}

void CoAP::Server::Act()
{

    MakeContext();

    while (true) {
        Process();
    }
}
void CoAP::Server::MakeContext()
{

    coap_resource_t * pResource = coap_resource_init(coap_make_str_const("test"), 0);

    coap_register_handler(pResource, Request, [](auto, auto,
                          const coap_pdu_t *request,
                          auto,
    coap_pdu_t *response) {
        (void)request;//TODO
        (void)response;//TODO
    });
    ctx.AddResource(pResource);
}
void CoAP::Server:: Process()
{
    ctx.iIoProcess(COAP_IO_NO_WAIT);

}


