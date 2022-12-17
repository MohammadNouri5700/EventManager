#include "grpcserver.h"
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"
#include <grpcpp/health_check_service_interface.h>
#include "mqttservice.h"
#include "wifiservice.h"
#include "convertservice.h"
#include "gpsservice.h"
#include "nodeservice.h"
#include "s7service.h"
#include "networkservice.h"
#include "serialservice.h"
#include "modbusservice.h"
#include "mqttpodservice.h"
#include "startupservice.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;

GrpcServer::GrpcServer(const std::string &address , CONNECTION::ConnectionManager *ConnMan)
{
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    MqttClientsConfigService *mqttclientsconfigservice = new MqttClientsConfigService(ConnMan) ;
    builder.RegisterService(mqttclientsconfigservice);

    SystemWifiConfigService *systemwificonfigservice = new SystemWifiConfigService() ;
    builder.RegisterService(systemwificonfigservice);

    SystemModbusConfigService *systemmodbusconfigservice = new SystemModbusConfigService(ConnMan) ;
    builder.RegisterService(systemmodbusconfigservice);

    SystemCommandService *systemcommandservice = new SystemCommandService();
    builder.RegisterService(systemcommandservice);

    MqttBrokerConfigService *mqttbrokerconfigservice = new MqttBrokerConfigService();
    builder.RegisterService(mqttbrokerconfigservice);

    SystemSnapSevenConfigService *systemsnapsevenconfigservice = new SystemSnapSevenConfigService(ConnMan);
    builder.RegisterService(systemsnapsevenconfigservice);

    SystemConvertProtocolConfigService *systemconvertprotocolconfigservice = new SystemConvertProtocolConfigService(ConnMan);
    builder.RegisterService(systemconvertprotocolconfigservice);
    
    MqttPodNodeConfigService *mqttPodNodeconfigservice = new MqttPodNodeConfigService() ;
    builder.RegisterService(mqttPodNodeconfigservice);

    SystemNodeConfigService *systemnodeconfigservice = new SystemNodeConfigService(ConnMan);
    builder.RegisterService(systemnodeconfigservice);

    SystemSerialConfigService *systemserialconfigservice = new SystemSerialConfigService(ConnMan);
    builder.RegisterService(systemserialconfigservice);

    SystemNetworkConfigService *systemnetworkconfigservice = new SystemNetworkConfigService(ConnMan);
    builder.RegisterService(systemnetworkconfigservice);

    SystemStartupConfigService *systemstartupconfigservice = new SystemStartupConfigService(ConnMan);
    builder.RegisterService(systemstartupconfigservice);

    gpsservice *GpsService = new gpsservice(ConnMan);
    builder.RegisterService(GpsService);

    // Finally assemble the server.
    server = builder.BuildAndStart();
    std::cout << "Server listening on " << address << std::endl;
}






