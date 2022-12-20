//
// Created by user on 12/5/22.
//

#include "gps.grpc.pb.h"
#include <iostream>
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"

#ifndef EVENT_MANAGER_GPSSERVICE_H
#define EVENT_MANAGER_GPSSERVICE_H

using namespace std;


struct GpsProtocol {
    std::string gpsName;
    std::string gpsId;
    ::int32_t interval;
    GpsDataType gpsDataType;
    bool gpsReciver;
};


class gpsservice : public SystemGpsProtocolConfig::Service  {
private:
    CONNECTION::ConnectionManager *connMan;
    std::vector<GpsProtocol> gpsConfig;
    ::grpc::Status SendSystemGpsProtocolConfig(::grpc::ServerContext *context, const ::ConfigGpsProtocol *request, ::GpsConfigResponse *response) override;

public:
    gpsservice(CONNECTION::ConnectionManager *ConnMan);

};


#endif //EVENT_MANAGER_GPSSERVICE_H
