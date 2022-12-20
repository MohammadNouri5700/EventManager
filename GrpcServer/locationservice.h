//
// Created by user on 12/17/22.
//


#include "gps.grpc.pb.h"
#include <iostream>
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"

#ifndef EVENT_MANAGER_LOCATIONSERVICE_H
#define EVENT_MANAGER_LOCATIONSERVICE_H

using namespace std;

class locationservice : public SystemGpsData::Service {
private:
    CONNECTION::ConnectionManager *connMan;
    ::grpc::Status SendSystemGpsData(::grpc::ServerContext *context, const ::CommandEx *request, ::GpsData *response) override;


public:
    locationservice(CONNECTION::ConnectionManager *ConnMan);

};


#endif //EVENT_MANAGER_LOCATIONSERVICE_H
