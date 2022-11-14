//
// Created by aziz on 16.08.21.
//

#ifndef EVENT_MANAGER_MASTERPROTOCOL_H
#define EVENT_MANAGER_MASTERPROTOCOL_H
#include "Protocol.h"
#include "../W_modbus/Master.h"
#include "../GateWay/Connection/ConnectionModbus.h"
#include "../GateWay/Node/ModBusTag.h"
namespace ProtocolS::ModBus
{

enum FunctionCode{
    ReadCoil=1 ,
    ReadDiscreteInputs=2,
    ReadMultipleHoldingRegisters=3,
    ReadInputRegisters=4,
    WriteSingleCoil=5,
    WritesingleHoldingRegister=6,
    WriteMultipleCoils=15,
    WiteMultipleHoldingRegisters=16,
    ReadandWriteMultipleRegisters=23
} ;
class MasterProtocol: public Protocol, public ModBUS::Master
{
public:
    MasterProtocol();
    virtual ~MasterProtocol();
    Modbus::Slave *slvCls;
    void Create(Connection *Conn) override;
    void OpenAndWrtie(Connection *Conn , Data* data);
    void Open(Connection *Conn) override;
    void Close() override;
    void KeepAlive() override;
    bool isOK() override;
    void Reconnect() override;
    void hasError() override;
    void DataReceived() override;
    void Listen() override;
    void UpdateTag(Tag *tag) override;
    void Write(Data* data,Tag* tag) override;
    ProtocolS::ModBusTag *FindModbusTag(std::string Name);

    void Stop();

protected:
    std::shared_ptr<ConnectionModbus> Conn_Modbus_{};
    Modbus::Slave *slv;
    std::atomic_bool bStopThread{false};

};
}


#endif //EVENT_MANAGER_MASTERPROTOCOL_H
