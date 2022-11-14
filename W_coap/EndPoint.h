//
// Created by aziz on 20.08.21.
//

#ifndef W_COAP_ENDPOINT_H
#define W_COAP_ENDPOINT_H
#include <coap3/coap.h>

class EndPoint
{
private:
    coap_endpoint_t *apEndpoint;
public:
    EndPoint(coap_endpoint_t *endpoint);
    EndPoint();
    EndPoint (coap_context_t *pContext, const coap_address_t *pListen_addr, coap_proto_t proto);
    virtual ~EndPoint();
    EndPoint(const EndPoint&) = delete;
    EndPoint operator=(const EndPoint&) = delete;

    coap_endpoint_t *pGetEndpoint() const;

    void SetEndPoint(coap_endpoint_t *pEndpoint);
    void New (coap_context_t *pContext, const coap_address_t *pListen_addr, coap_proto_t proto);
    void SetDefaultMtu (unsigned mtu);
    void Free();
};


#endif //W_COAP_ENDPOINT_H
