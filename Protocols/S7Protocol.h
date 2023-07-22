//
// Created by aziz on 24.08.21.
//

#ifndef EVENT_MANAGER_S7PROTOCOL_H
#define EVENT_MANAGER_S7PROTOCOL_H
#include "Protocol.h"
#include "../W_S7/S7Client.h"
#include "../GateWay/Connection/ConnectionS7.h"
#include "../GateWay/Data.h"
#include "../GateWay/Node/S7Tag.h"

namespace ProtocolS::S7
{
    class S7Protocol : public ProtocolS::Protocol, public Snap7::S7Client
    {
    public:
        S7Protocol();
        virtual ~S7Protocol();
        void Listen() override;
        void Create(Connection *Conn) override;
        void CreateAndWrite(Connection *Conn, Data *data);
        ProtocolS::S7Tag *FindS7Tag(std::string name);
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
        void SetBitAt(byte buffer[], int Pos, int Bit, bool Value);

    private:
        int Size(std::string str);
        void ReverseBytes(void *start, int size);
    };
}

#endif // EVENT_MANAGER_S7PROTOCOL_H
