//
// Created by aziz on 20.08.21.
//

#include "EndPoint.h"

EndPoint::EndPoint(coap_endpoint_t *endpoint) : apEndpoint(endpoint) {}

EndPoint::EndPoint() : 
    apEndpoint(nullptr)
{
}

EndPoint::~EndPoint()
{

}

coap_endpoint_t *EndPoint::pGetEndpoint() const
{
    return apEndpoint;
}

void EndPoint::SetEndPoint(coap_endpoint_t *endpoint)
{
    EndPoint::apEndpoint = endpoint;
}

EndPoint::EndPoint(coap_context_t *context, const coap_address_t *listen_addr, coap_proto_t proto) : 
    apEndpoint (coap_new_endpoint(context, listen_addr, proto))
{
}

void EndPoint::New(coap_context_t *context, const coap_address_t *listen_addr, coap_proto_t proto)
{
    apEndpoint = coap_new_endpoint (context, listen_addr, proto);
}

void EndPoint::SetDefaultMtu(unsigned int mtu)
{
    coap_endpoint_set_default_mtu (apEndpoint, mtu);
}

void EndPoint::Free()
{
    coap_free_endpoint (apEndpoint);
}
