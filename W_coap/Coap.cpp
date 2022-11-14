//
// Created by aziz on 16.08.21.
//

#include "Coap.h"

#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

CoAP::Coap::Coap() : Destination{}, ctx{}
{
    Start();

}

CoAP::Coap::~Coap()
{
}

void CoAP::Coap::Run()
{

    //Init();
    Act();
    //End();
}

void CoAP::Coap::Start()
{
    coap_startup();
}

void CoAP::Coap::Init()
{

    if (ResolveAddress() < 0) {
        coap_log(LOG_CRIT, "failed to resolve address\n");
        End();
    }

    if (!ctx) {
        coap_log(LOG_EMERG, "cannot creat Context\n");
        End();
    }

}
void CoAP::Coap::End()
{
    ctx.Free();
    coap_cleanup();
}

int CoAP::Coap::ResolveAddress()
{

    struct addrinfo *res, *ainfo;
    struct addrinfo hints;
    int error, len=-1;

    memset(&hints, 0, sizeof(hints));
    memset(&Destination, 0, sizeof(Destination));
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family = AF_UNSPEC;

    error = getaddrinfo(strHost.c_str(), strService.c_str(), &hints, &res);

    if (error != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(error) <<  std::endl;
        return error;
    }

    for (ainfo = res; ainfo != nullptr; ainfo = ainfo->ai_next) {
        switch (ainfo->ai_family) {
        case AF_INET6:
        case AF_INET:
            len = Destination.size = ainfo->ai_addrlen;
            memcpy(&Destination.addr.sin6, ainfo->ai_addr, Destination.size);
            goto finish;
        default:
            ;
        }
    }

finish:
    freeaddrinfo(res);
    return len;
}

void CoAP::Coap::SetAddress(std::string h, std::string s)
{
    strHost = {h};
    strService = {s};
}