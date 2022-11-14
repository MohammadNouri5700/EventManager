//
// Created by aziz on 03.08.21.
//

#ifndef EVENT_MANAGER_CANPROTOCOL_H
#define EVENT_MANAGER_CANPROTOCOL_H
#include "../W_can/cancontroller.h"
#include "Protocol.h"
#include "../GateWay/Connection/ConnectionCan.h"
#include "../GateWay/Node/CanTag.h"

namespace ProtocolS::CAN
{
    class CANProtocol : public ProtocolS::Protocol
    {
    public:
        ::CAN::CanController* CanClient;
        ConnectionCAN *conn;
        CANProtocol();
        CANProtocol(ConnectionCAN *Conn);
        virtual ~CANProtocol();
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
        void Write(Data *data, Tag *tag) override;
        void Stop();
    private:
    int Size(std::string str);
    };
}

#endif // EVENT_MANAGER_CANPROTOCOL_H
