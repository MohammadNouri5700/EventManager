//
// Created by aziz on 19.08.21.
//

#include "Resource.h"

Resource::Resource(coap_resource_t *resource) : pResource(resource) {}

Resource::Resource(): 
    pResource(nullptr)
{
}

Resource::~Resource()
{


}

coap_resource_t *Resource::pGetResource() const
{
    return pResource;
}

void Resource::SetResource(coap_resource_t *resource)
{
    Resource::pResource = resource;
}

void Resource::Init(coap_str_const_t *uri_path, int flags)
{
    pResource = coap_resource_init(uri_path, flags);
}

void Resource::ProxyUriInit(coap_method_handler_t handler, size_t host_name_count, const char **host_name_list)
{
    pResource = coap_resource_proxy_uri_init(handler, host_name_count, host_name_list);

}

void Resource::SetMode(int mode)
{
    coap_resource_set_mode(pResource, mode );
}

void Resource::SetUserdata(void *data)
{
    coap_resource_set_userdata(pResource, data );
}

void Resource::UnknownInit(coap_method_handler_t put_handler)
{
    pResource = coap_resource_unknown_init(put_handler);
}
