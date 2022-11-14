//
// Created by aziz on 17.10.21.
//

#ifndef EVENT_MANAGER_COAPPROTOCOL_H
#define EVENT_MANAGER_COAPPROTOCOL_H
#include "Protocol.h"
#include "../W_coap/CoapNode.h"

namespace ProtocolS::COAP
{
class CoapProtocol:public ProtocolS::Protocol, public CoAP::CoapNode
{
public:
    void Listen() override;

    void Create(Connection *Conn) override;

    void Open(Connection *Conn) override;

    void Close() override;

    void KeepAlive() override;

    bool isOK() override;

    void Reconnect() override;

    void hasError() override;

    void DataReceived() override;

    ~CoapProtocol() override;

    void Write(Data* data,Tag* tag) override;

    void UpdateTag(Tag *tag) override;
};
}


#endif //EVENT_MANAGER_COAPPROTOCOL_H
