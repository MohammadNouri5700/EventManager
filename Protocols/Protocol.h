//
// Created by aziz on 03.08.21.
//

#ifndef EVENT_MANAGER_PROTOCOL_H
#define EVENT_MANAGER_PROTOCOL_H

#include <any>
#include <list>
#include <functional>
#include "../GateWay/Connection/Connection.h"
#include "../GateWay/Data.h"


namespace ProtocolS
{
class Tag;
class Protocol
{
public:
    std::list<Tag*> Observer{};
    Protocol();
    virtual ~Protocol();
    virtual void Listen() = 0;
    virtual void Create(Connection *Conn)=0;
    virtual void Open(Connection *Con) = 0;
    virtual void Close() = 0;
    virtual void KeepAlive() = 0 ;
    virtual bool isOK() = 0 ;
    virtual void Reconnect() = 0;
    virtual void hasError() = 0;
    virtual void DataReceived() =0;
    virtual void UpdateTag(Tag* tag);
    virtual void Write(Data* data,Tag* tag) {(void)tag;/*TODO*/};
    void Attach(Tag* tag);
    void Detach(Tag* tag);
};
}


#endif //EVENT_MANAGER_PROTOCOL_H
