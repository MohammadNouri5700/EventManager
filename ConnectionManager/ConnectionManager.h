//
// Created by aziz on 09.10.21.
//

#ifndef EVENT_MANAGER_CONNECTIONMANAGER_H
#define EVENT_MANAGER_CONNECTIONMANAGER_H

#include "../GateWay/Node/Tag.h"
#include "../GateWay/Connection/Connection.h"
#include "../GateWay/ConvertS/Convert.h"
namespace CONNECTION
{
class ConnectionManager
{
public:
    void Create();
    void KeepAlive();
    bool isOK();
    void Reconnect();
    void hasError();
    void DataReceived();

    void AddConnection(ProtocolS::Protocol* pro);
    void AddConvert(Convert Conn);
};
}


#endif //EVENT_MANAGER_CONNECTIONMANAGER_H
