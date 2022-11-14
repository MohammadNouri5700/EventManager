//
// Created by aziz on 16.08.21.
//

#ifndef W_COAP_CLIENT_H
#define W_COAP_CLIENT_H
#include "Coap.h"
#include "Sessions.h"
#include "Pdu.h"

namespace CoAP
{
class client: public Coap
{
protected:
    Pdu pdu;
    //coap_session_t *Session = nullptr;
    Sessions Session;
    coap_response_handler_t handler;

    coap_pdu_type_t type{COAP_MESSAGE_CON};
    coap_pdu_code_t code{COAP_REQUEST_CODE_GET};

    virtual void Act();
    virtual void End();
    virtual void Init();
    virtual void Process();
    virtual void make_pdu();
    virtual void make_session();
public:
    void set_handler(coap_response_handler_t handler)
    {
        this->handler = handler;
    };
    void set_type(coap_pdu_type_t type)
    {
        this-> type = type;
    }
    void set_code(coap_pdu_code_t code)
    {
        this-> code = code;
    }

    client();
    ~client();

};
}

#endif //W_COAP_CLIENT_H
