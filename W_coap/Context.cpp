//
// Created by aziz on 16.08.21.
//

#include "Context.h"
#include <string>
#include <iostream>

CoAP::Context::Context()
{
    apContext = coap_new_context(nullptr);
}

CoAP::Context::Context(const coap_address_t *addr)
{
    apContext = coap_new_context(addr) ;
}

CoAP::Context::~Context()
{
    apContext = coap_new_context(nullptr);
}

void CoAP::Context::Free()
{
    coap_free_context(apContext);
}

void CoAP::Context::Handler(coap_response_handler_t handler)
{
    coap_register_response_handler(apContext, handler);
}

void CoAP::Context::AddResource(coap_resource_t *resource)
{
    coap_add_resource (apContext, resource );
}

int CoAP::Context::iIoProcess(uint32_t timeout_ms)
{
    return coap_io_process(apContext, timeout_ms);
}

void *CoAP::Context::pGetAppData()
{
    return coap_get_app_data(apContext);
}

void CoAP::Context::ResourceReleaseUserdataHandler(coap_resource_release_userdata_handler_t callback)
{
    coap_resource_release_userdata_handler(apContext, callback );
}

CoAP::Context::Context(coap_context_t *context) : apContext(context) {}

coap_context_t *CoAP::Context::pGetContext() const
{
    return apContext;
}

void CoAP::Context::SetContext(coap_context_t *context)
{
    Context::apContext = context;
}



