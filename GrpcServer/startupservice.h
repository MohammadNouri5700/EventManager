#pragma once

#include "startup.grpc.pb.h"
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"
class SystemStartupConfigService final : public SystemStartupConfig::Service
{
    private:
        virtual ::grpc::Status SendSystemStartupConfig(::grpc::ServerContext *context, const ::StartupConfig *request, ::StartupResponse *response) override;
        void ExtractStartupConfig();
    public:
        SystemStartupConfigService(CONNECTION::ConnectionManager *ConnMan);
};
