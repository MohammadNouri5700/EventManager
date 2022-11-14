//
// Created by aziz on 19.12.21.
//

#ifndef EVENT_MANAGER_CENTRALPROTOCOL_H
#define EVENT_MANAGER_CENTRALPROTOCOL_H
#include "Protocol.h"

namespace ProtocolS
{
class CentralProtocol: public Protocol
{
public:
    ~CentralProtocol() override;

    void Listen() override;

    void Create(Connection *Conn) override;

    void Open(Connection *Conn) override;

    void Close() override;

    void KeepAlive() override;

    bool isOK() override;

    void Reconnect() override;

    void hasError() override;

    void DataReceived() override;

    void UpdateTag(Tag *tag) override;

    void Write(Data* data,Tag* tag) override;
};
}


#endif //EVENT_MANAGER_CENTRALPROTOCOL_H
