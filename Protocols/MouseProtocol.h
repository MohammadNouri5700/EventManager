//
// Created by aziz on 13.12.21.
//

#ifndef EVENT_MANAGER_MOUSEPROTOCOL_H
#define EVENT_MANAGER_MOUSEPROTOCOL_H
#include "Protocol.h"
#include "../MouseKey/mouse.h"

namespace ProtocolS::MOUSE
{
class MouseProtocol:public Protocol, public mouse
{
public:
    MouseProtocol();

    ~MouseProtocol() override;

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


#endif //EVENT_MANAGER_MOUSEPROTOCOL_H
