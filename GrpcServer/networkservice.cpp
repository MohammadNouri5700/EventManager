#include "networkservice.h"
#include <iostream>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>

#include "../GateWay/Node/NodeList.h"
#include "../GateWay/ConvertS/OutputNode.h"
#include "../GateWay/Connection/xmlnetwork.h"
using namespace grpc;
extern Network network;
SystemNetworkConfigService::SystemNetworkConfigService(CONNECTION::ConnectionManager *ConnMan)
{
    // connMan = ConnMan;
}

void SystemNetworkConfigService::ApplyNetworkConfig()
{
    ApplyIP();
    ApplyDNS();
}


void SystemNetworkConfigService::ApplyIP()
{
    std:string cmd;
	//network interface

	//clean up all ip addresses
	// cmd = "ip addr flush dev " + network.Name ;
	// system(cmd.c_str()); 

    // for(auto ot :OTNetworkConfig){
    //     cmd = "ip address add " + network.IP + "/24 dev " + network.Name;
    //     std::cout << cmd << std::endl;
    //     system(cmd.c_str()); 
    // }
    
}

void SystemNetworkConfigService::ApplyDNS()
{
}

::grpc::Status SystemNetworkConfigService::SendSystemNetworkConfig(::grpc::ServerContext *context, const ::GatewayNetworksConfig *request, ::NetworkResponse *response)
{

    std::cout << "Received Network Config request" << std::endl;
    NetworksConfig networksConfig;

    dhcpEnabled = request->otnetworkconfig().dhcpenabled();

    std::cout << "############## request->otnetworkconfig().networkipconfig().size():" << request->networkipconfig().size() << std::endl;

    for (auto &configIP : request->networkipconfig())
    {

        networksConfig.netIP = configIP.netip();
        std::cout << "############## networksConfig.netIP:" << networksConfig.netIP << std::endl;
        networksConfig.defaultGate = configIP.defaultgate();
        std::cout << "############## networksConfig.defaultGate" << networksConfig.defaultGate << std::endl;
        networksConfig.netMask = configIP.netmask();
        OTNetworkConfig.push_back(networksConfig);
    }
    for (auto &configDNS : request->networkdnsconfig())
    {

        std::string dnsconfig = configDNS.dnsconfig();
        std::cout << "############## dnsconfig:" << dnsconfig << std::endl;
        OTDNSConfig.push_back(dnsconfig);
    }
    ApplyNetworkConfig();
    return Status::OK;
}
