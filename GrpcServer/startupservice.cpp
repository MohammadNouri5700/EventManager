#include "startupservice.h"
#include <iostream>
#include "../GateWay/Node/NodeList.h"
#include "../GateWay/ConvertS/OutputNode.h"
using namespace grpc;
extern std::vector<OutputNode *> OutnodeS;

SystemStartupConfigService::SystemStartupConfigService(CONNECTION::ConnectionManager *ConnMan){
    //connMan = ConnMan;
}


::grpc::Status SystemStartupConfigService::SendSystemStartupConfig(::grpc::ServerContext* context, const ::StartupConfig* request, ::StartupResponse* response) {


    std::cout << "Received Startup Config request" << std::endl;    
    response->set_success(true);
    response->set_errorcode(0);
    response->set_errordesc("success");
    return Status::OK;
}



