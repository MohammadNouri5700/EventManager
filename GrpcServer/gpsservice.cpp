//
// Created by user on 12/5/22.
//

#include "gpsservice.h"

gpsservice::gpsservice(CONNECTION::ConnectionManager *ConnMan) {
    connMan = ConnMan;
}

::grpc::Status
gpsservice::SendSystemGpsProtocolConfig(::grpc::ServerContext *context, const ::ConfigGpsProtocol *request,
                                        ::GpsConfigResponse *response) {

    std::cout << "Received Gps Config request  name sample : " << request->gpsprotocol().Get(0).gpsname() << std::endl;






    return Service::SendSystemGpsProtocolConfig(context, request, response);
}


