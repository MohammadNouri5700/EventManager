#pragma once
#ifndef MODBUS_SERVICE_H
#define MODBUS_SERVICE_H
#include "modbus.grpc.pb.h"
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"



struct ModbusRTUSlaves {
    std::string clientName ;
    std::string clientID ;
    BaudRate baudRate;
    Parity parity;
    int32_t startBit;
    int32_t stopBit;        
    int32_t dataBit;
};

struct ModbusTCPSlaves{
    std::string clientName ;
    std::string clientID ;
    std::string IP;
    int32_t port;
};

struct ModbusTag{
    std::string tagName;
    std::string tagId;
    std::string serverId;
    ModbusDataType dataType;
    FunctionCode functionCode;
    int32_t numberOfRegisters;
    int32_t intervalTime;
    int32_t startingAddress;
};
struct ModbusDeviceConfig {
    bool rtuOrTcp ;
    
    
    ModbusRTUSlaves modbusRTUSlaves;
    ModbusTCPSlaves modbusTCPSlaves;

    std::vector<ModbusTag> modbusTag;
};


class SystemModbusConfigService final : public SystemModbusConfig::Service { 
    private: 
        CONNECTION::ConnectionManager *connMan;
        std::vector<struct ModbusDeviceConfig> modbusConfig;
        std::map<ModbusDataType,std::string> mDataType;
        virtual ::grpc::Status SendSystemModbusConfig(::grpc::ServerContext* context, const ::ModbusConfig* request, ::ModbusConfigResponse* response) override;
        void ExtractModbusConfig();
    public :
        SystemModbusConfigService(CONNECTION::ConnectionManager *ConnMan);
};
#endif //MODBUS_SERVICE_H