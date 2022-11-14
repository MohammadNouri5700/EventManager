//
// Created by aziz on 19.08.21.
//

#ifndef W_COAP_RESOURCE_H
#define W_COAP_RESOURCE_H
#include <coap3/coap.h>

class Resource
{
private:
    coap_resource_t* pResource;
public:
    Resource(coap_resource_t *resource);
    Resource();
    virtual ~Resource();
    Resource(const Resource&) = delete;
    Resource operator=(const Resource&) = delete;

    void Init(coap_str_const_t * uri_path, int flags);
    void ProxyUriInit(coap_method_handler_t handler, size_t	host_name_count, const char **host_name_list);
    void SetMode(int mode);
    void SetUserdata(void * data);
    void UnknownInit(coap_method_handler_t put_handler	);

    coap_resource_t *pGetResource() const;

    void SetResource(coap_resource_t *resource);

};


#endif //W_COAP_RESOURCE_H
