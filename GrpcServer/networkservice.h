#pragma once

#include "network.grpc.pb.h"
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"


struct NetworksConfig
{
    std::string netIP ;
    std::string netMask ;
    std::string defaultGate ;
};


class SystemNetworkConfigService final : public SystemNetworkConfig::Service
{
    private:
        bool dhcpEnabled;  
        std::vector<NetworksConfig> OTNetworkConfig;
        std::vector<std::string> OTDNSConfig;
        virtual ::grpc::Status SendSystemNetworkConfig(::grpc::ServerContext *context, const ::GatewayNetworksConfig *request, ::NetworkResponse *response) override;
        void ApplyNetworkConfig();
        /// @brief Apply IP configuration to the specified network interface
        void ApplyIP();
        /// @brief Apply DNS configuration to the specified network interface
        void ApplyDNS();

    public:
        SystemNetworkConfigService(CONNECTION::ConnectionManager *ConnMan);
};
