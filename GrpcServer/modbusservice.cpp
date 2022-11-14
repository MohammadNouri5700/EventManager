
#include "../Protocols/MasterProtocol.h"
#include "modbusservice.h"
#include "../GateWay/Connection/ConnectionModbus.h"
#include "../GateWay/Node/NodeList.h"
#include "../GateWay/Node/ModBusTag.h"
#include <iostream>

using namespace grpc;

extern std::vector<Connection *> ConnectionS;


::ModbusTag ModbusDeviceTagGrpc(const ModbusConfig::ModbusDevice::ModbusTag tag)
{
    ::ModbusTag modbusTag;
    modbusTag.tagName = tag.tagname();
    modbusTag.dataType = tag.datatype();
    modbusTag.tagId = tag.tagid();
    modbusTag.serverId = tag.serverid();
    modbusTag.intervalTime = tag.intervaltime();
    modbusTag.numberOfRegisters = tag.numberofregisters();
    modbusTag.startingAddress = tag.startingaddress();
    modbusTag.functionCode = tag.functioncode();
    return modbusTag;
}

::ModbusRTUSlaves ModbusRTUSlavesGrpc(const ModbusConfig::ModbusDevice::ModbusRTUSlaves slave)
{
    ::ModbusRTUSlaves rtuSlaves;
    rtuSlaves.baudRate = slave.baudrate();
    rtuSlaves.dataBit = slave.databit();
    rtuSlaves.parity = slave.parity();
    rtuSlaves.startBit = slave.startbit();
    rtuSlaves.stopBit = slave.stopbit();
    return rtuSlaves;
}

::ModbusTCPSlaves ModbusTCPSlavesGrpc(const ModbusConfig::ModbusDevice::ModbusTCPSlaves slave)
{
    ::ModbusTCPSlaves tcpSlaves;
    tcpSlaves.IP = slave.ip();
    tcpSlaves.port = slave.port();
    return tcpSlaves;
}

void SystemModbusConfigService::ExtractModbusConfig()
{
    // int Counter = 0; 
    // for (auto p:ConnectionS) {
    //     if(p->IProtocol == ProtocolIIOT::MODBUS)
    //     {
    //     ConnectionS.erase(ConnectionS.begin() +Counter);
    //     }
    // Counter ++;
    // }
    ConnectionModbus *modbus = new ConnectionModbus{};
    for(const ModbusDeviceConfig x : modbusConfig){
        modbus->IProtocol = ProtocolIIOT::MODBUS;
        if(x.rtuOrTcp){
            modbus->Address.Value=x.modbusTCPSlaves.IP + ":" + std::to_string(x.modbusTCPSlaves.port);
            modbus->SlaveNumber.Value = 1;

        } else{
             modbus->Address.Value = "192.168.0.125:50053";
            modbus->SlaveNumber.Value = 1;

        //ToDO
        }

        for(const auto t : x.modbusTag){
            xmlModBus *node = new xmlModBus;
            node->Name.Value = t.tagName;
            node->Function.Value = t.functionCode;
            node->Timer.Value = t.intervalTime;
            node->ValueType.Value =  mDataType[t.dataType];
            node->NumberOfRegisters.Value = 1;//t.numberOfRegisters;
            node->StartingAddress.Value = t.startingAddress;
            modbus->NodeS.push_back(node);
        }
    }

    auto m = reinterpret_cast<ConnectionModbus *>(modbus);
    ProtocolS::ModBus::MasterProtocol *master{new ProtocolS::ModBus::MasterProtocol()};
    master->Create(m);

    for (auto& node : nodeList) {
        int Counter  = 0;    
        auto &tags = node;
        for (auto tag : tags.second) {
            if (tag->TagType == ProtocolIIOT::MODBUS) {
                std::cout << tag->strGetName() << "Found Tag to Delete" << Counter << std::endl;
                tags.second.clear();
            }
            Counter ++; 
        }
        std::cout << "tag Deleted : " << tags.second.size() << std::endl;
    }


    ProtocolS::Node n;
    n.first = m->Name.Value;
    for (auto t : m->NodeS)
    {
        auto mq = reinterpret_cast<xmlModBus *>(t);
        ProtocolS::ModBusTag *mn{new ProtocolS::ModBusTag(mq)};
        n.second.push_back(mn);
    }
    nodeList.push_back(std::move(n));

    for (auto [i, n] : nodeList)
    {
        if (strcmp(i.c_str(), m->Name.Value.c_str()) == 0)
            for (auto t : n)
            {
                t->setSubject(master);
                 t->conn = m;
                t->TagType = ProtocolIIOT::MODBUS;
                t->Timer.Value = 1;
            }
    };
    ConnectionS.push_back(modbus);
    connMan->AddConnection(master);
}

SystemModbusConfigService::SystemModbusConfigService(CONNECTION::ConnectionManager *ConnMan)
{
    connMan = ConnMan;
}

::grpc::Status SystemModbusConfigService::SendSystemModbusConfig(::grpc::ServerContext *context, const ::ModbusConfig *request,
                                                                 ::ModbusConfigResponse *response)
{
   std::cout << "Received Modbus Config request" << std::endl;
   mDataType[ModbusDataType::MBOOLEAN] = "bool";
   mDataType[ModbusDataType::MINT8] = "int8";
   mDataType[ModbusDataType::MUINT8] = "uint8";
   mDataType[ModbusDataType::MINT16] = "int16";
   mDataType[ModbusDataType::MUINT16] = "uint16";
   mDataType[ModbusDataType::MINT32] = "int";
   mDataType[ModbusDataType::MINT64] = "int64";
   mDataType[ModbusDataType::MFLOAT32] = "float";
   mDataType[ModbusDataType::MFLOAT64] = "float64";
   mDataType[ModbusDataType::MSTRING] = "string";

   // //...
   // m[Sun] = "Sunday";

   modbusConfig.clear();
    ModbusDeviceConfig modbusDeviceConfig;
    for (auto &configmodbus : request->modbusdevice())
    {
        modbusDeviceConfig.rtuOrTcp = configmodbus.rtuortcp();
        
        if (configmodbus.rtuortcp())
        {
             modbusDeviceConfig.modbusTCPSlaves = ModbusTCPSlavesGrpc(configmodbus.modbustcpslaves());
        }else{
            modbusDeviceConfig.modbusRTUSlaves = ModbusRTUSlavesGrpc(configmodbus.modbusrtuslaves());
           
        }
        for (auto &tag : configmodbus.modbustag())
        {
            modbusDeviceConfig.modbusTag.push_back(ModbusDeviceTagGrpc(tag));
        }
        modbusConfig.push_back(modbusDeviceConfig);
    }
    if (modbusConfig.size()==0)
    {
        std::cout << "There is not any Tags in Modbus Config request" << std::endl;
       return Status::CANCELLED;
    }
    
    ExtractModbusConfig();
    return Status::OK;
}
