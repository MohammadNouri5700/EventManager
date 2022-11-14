//
// Created by aziz on 16.08.21.
//

#ifndef W_COAP_SERVER_H
#define W_COAP_SERVER_H
#include "Coap.h"

namespace CoAP
{
class Server: public Coap
{

protected:

    coap_endpoint_t *pEndPoint{nullptr};
    std::string strUri{"test"};
    coap_method_handler_t  Handler;
    coap_resource_t *pResource {nullptr};
    coap_request_t Request{COAP_REQUEST_GET};

    virtual void Init();
    virtual void Act();
    virtual void Process();
    virtual void MakeContext();

public:

    Server();
    virtual ~Server();
    Server(const Server&) = delete;
    Server operator=(const Server&) = delete;
    void SetHandler(coap_method_handler_t handler)
    {
        this->Handler = handler;
    };
    void SetRequest(coap_request_t req)
    {
        Request = req;
    };
    void SetUri(std::string uri)
    {
        this->strUri = uri;
    };
};
}


#endif //W_COAP_SERVER_H
