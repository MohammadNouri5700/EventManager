#pragma once

#include "serialconfig.grpc.pb.h"
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"

 struct RsConfig{
        bool enabled =1;
        SerialBaudRate serialBaudRate;
        int32_t endBit;
        SerialParity serialParity;
        int32_t dataBit;
} ;


class SystemSerialConfigService final : public SystemSerialConfig::Service
{
    private:
        RsConfig rs232Config;
        RsConfig rs485Config;
        virtual ::grpc::Status SendSystemSerialConfig(::grpc::ServerContext *context, const ::SerialConfig *request, ::SerialResponse *response) override;
        void ExtractSerialConfig();
        u_int32_t EnumToNumberBaud(SerialBaudRate serialBaudRate);
        u_int32_t EnumToNumberParity(SerialParity serialParity);
    public:
        SystemSerialConfigService(CONNECTION::ConnectionManager *ConnMan);
};
