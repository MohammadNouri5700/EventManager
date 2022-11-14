#pragma once

#include "wifi.grpc.pb.h"

class SystemWifiConfigService final : public SystemWifiConfig::Service {  
    virtual ::grpc::Status SendSystemWifiConfig(::grpc::ServerContext* context, const ::ConfigWifi* request, ::ConfigWifi* response) override;
};

class SystemCommandService final : public SystemCommand::Service {
    virtual ::grpc::Status SendSystemCommand(::grpc::ServerContext* context, const ::Command* request, ::CommandResponce* response) override;
};