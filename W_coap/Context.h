//
// Created by aziz on 16.08.21.
//

#ifndef W_COAP_CONTEXT_H
#define W_COAP_CONTEXT_H
#include <coap3/coap.h>

namespace CoAP
{

class Context
{
private:
    coap_context_t * apContext{nullptr};
public:

    Context();
    Context(const coap_address_t * pAddr);
    Context(const Context&) = delete;
    Context operator=(const Context&) = delete;

    Context(coap_context_t *context);
    ~Context();
    void Free();
    void Handler(coap_response_handler_t handler);
    void AddResource (coap_resource_t * pResource );
    int  iIoProcess(uint32_t timeout_ms);
    void* pGetAppData();
    bool operator!()
    {
        return !apContext;
    }
    coap_context_t * pGet()
    {
        return  apContext;
    }
    void ResourceReleaseUserdataHandler	(coap_resource_release_userdata_handler_t callback);

    coap_context_t* pGetContext() const;

    void SetContext(coap_context_t *context);

};

}

#endif //W_COAP_CONTEXT_H
