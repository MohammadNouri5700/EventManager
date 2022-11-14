#include "convertservice.h"
#include <iostream>
#include "../GateWay/ConvertS/Convert.h"

using namespace grpc;


SystemConvertProtocolConfigService::SystemConvertProtocolConfigService(CONNECTION::ConnectionManager *ConnMan){
    connMan = ConnMan;
}
::grpc::Status SystemConvertProtocolConfigService::SendSystemConvertProtocolConfig(::grpc::ServerContext* context, const ::ConfigConvertProtocol* request, ::ConvertProtocolConfigResponse* response) {


    std::cout << "Received Convert Protocol Config request" << std::endl;    
    
    for (auto &configConvertProtocol : request->convertprotocol()) {
        Convert tempConvert;
        tempConvert.setDist(configConvertProtocol.tagnamedist()) ;
        tempConvert.setSource(configConvertProtocol.tagnamesource()) ;
        std::cout << configConvertProtocol.tagnamesource() << "====" << configConvertProtocol.tagnamedist() <<"==="<<std::endl;
        //tempConvertConfig.timer = configConvertProtocol.timer();
        //convertConfig.push_back(tempConvert);
        connMan->AddConvert(tempConvert);
    }
    return Status::OK;
}



