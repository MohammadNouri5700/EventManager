//
// Created by aziz on 20.08.21.
//

#ifndef EVENT_MANAGER_SERVERPROTOCOL_H
#define EVENT_MANAGER_SERVERPROTOCOL_H
#include "Protocol.h"
#include "../W_coap/Server.h"



namespace ProtocolS::COAP
{
class ServerProtocol: public ProtocolS::Protocol, public CoAP::Server
{
public:
    void Listen() override;
    virtual ~ServerProtocol();
    ServerProtocol();

    void UpdateTag(Tag *tag) override;

    void Create(Connection *Conn) override;

    void Open(Connection *Conn) override;

    void Close() override;

    void KeepAlive() override;

    bool isOK() override;

    void Reconnect() override;

    void hasError() override;

    void DataReceived() override;

    void Write(Data* data,Tag* tag) override;
};
}


#endif //EVENT_MANAGER_SERVERPROTOCOL_H
