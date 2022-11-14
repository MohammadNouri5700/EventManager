//
// Created by aziz on 13.12.21.
//

#ifndef EVENT_MANAGER_KEYPROTOCOL_H
#define EVENT_MANAGER_KEYPROTOCOL_H
#include "Protocol.h"
#include "../MouseKey/key.h"
namespace ProtocolS::KEY
{
class KeyProtocol: public Protocol, public key
{
public:
    ~KeyProtocol() override;

    KeyProtocol();

    void Listen() override;

    void Create(Connection *Conn) override;

    void Open(Connection *Conn) override;

    void UpdateTag(Tag *tag) override;

    void Close() override;

    void KeepAlive() override;

    bool isOK() override;

    void Reconnect() override;

    void hasError() override;

    void DataReceived() override;

};
}

#endif //EVENT_MANAGER_KEYPROTOCOL_H
