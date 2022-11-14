#pragma once

#include "convert.grpc.pb.h"
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"


struct ConvertConfig
{
    std::string tagNameSource;
    std::string tagNameDist;
    int32_t timer;
};

class SystemConvertProtocolConfigService final : public SystemConvertProtocolConfig::Service
{
private:
    CONNECTION::ConnectionManager *connMan;
    std::vector<ConvertConfig> convertConfig;
    virtual ::grpc::Status SendSystemConvertProtocolConfig(::grpc::ServerContext *context, const ::ConfigConvertProtocol *request, ::ConvertProtocolConfigResponse *response) override;
public:
    SystemConvertProtocolConfigService(CONNECTION::ConnectionManager *ConnMan);
};
