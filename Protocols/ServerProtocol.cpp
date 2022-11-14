//
// Created by aziz on 20.08.21.
//

#include "ServerProtocol.h"
#include "../GateWay/Node/CoapTag.h"

coap_request_t RequestType(std::string str)
{
    if (strcmp(str.c_str(), "GET")==0)
        return COAP_REQUEST_GET;
    if (strcmp(str.c_str(), "POST")==0)
        return COAP_REQUEST_POST;
    if (strcmp(str.c_str(), "PUT")==0)
        return COAP_REQUEST_PUT;
    if (strcmp(str.c_str(), "DELETE")==0)
        return COAP_REQUEST_DELETE;
    if (strcmp(str.c_str(), "FETCH")==0)
        return COAP_REQUEST_FETCH;
    if (strcmp(str.c_str(), "PATCH")==0)
        return COAP_REQUEST_PATCH;
    if (strcmp(str.c_str(), "IPATCH")==0)
        return COAP_REQUEST_IPATCH;

    return COAP_REQUEST_GET;
}


void ProtocolS::COAP::ServerProtocol::Listen()
{
    CoAP::Server::Run();
}

ProtocolS::COAP::ServerProtocol::ServerProtocol() {}

ProtocolS::COAP::ServerProtocol::~ServerProtocol()
{

}

void ProtocolS::COAP::ServerProtocol::Create(Connection *Conn)
{
    (void)Conn;
    coap_method_handler_t handler = [](coap_resource_t *r, auto, const coap_pdu_t *request, auto, coap_pdu_t *response) {

        coap_str_const_t * s = coap_resource_get_uri_path(r) ;

        std::string ss(s->s, s->s+s->length);
        std::cout <<"\nuri : " << ss << '\n';
        size_t l;
        const uint8_t *data;
        coap_get_data(request, &l, &data);
        std::string Data(data, data+l);
        std::cout << Data;
        std::cout <<"\n";

        std::string str = "please waite";
        coap_pdu_set_code(response, COAP_RESPONSE_CODE_CONTENT);
        coap_add_data(response, str.size(), (const uint8_t *)str.c_str());
    };
    SetHandler(handler);
}

void ProtocolS::COAP::ServerProtocol::Open(Connection *Conn)
{
    Init();
    std::cout<<"\nsize :"<<Observer.size()<<"\n";
    for (auto i:Observer) {
        (void)i; // TODO
        //auto n = reinterpret_cast<CoapTag*>(i); // TODO: what is it?
        MakeContext();
        break;
    }
}

void ProtocolS::COAP::ServerProtocol::Close()
{

}

void ProtocolS::COAP::ServerProtocol::KeepAlive()
{

}

bool ProtocolS::COAP::ServerProtocol::isOK()
{
    return false;
}

void ProtocolS::COAP::ServerProtocol::Reconnect()
{

}

void ProtocolS::COAP::ServerProtocol::hasError()
{

}

void ProtocolS::COAP::ServerProtocol::DataReceived()
{

}

void ProtocolS::COAP::ServerProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}

void ProtocolS::COAP::ServerProtocol::Write(Data* data,Tag* tag)
{
    Protocol::Write(data,tag);
}
