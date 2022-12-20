//
// Created by MohammadNouri on 12/17/22.
//

#include "locationservice.h"
#include "../GateWay/Connection/ConnectionGPS.h"
#include "../GateWay/Node/GpsTag.h"
#include "../GateWay/Node/NodeList.h"

extern std::vector<Connection *> ConnectionS;
extern ProtocolS::NodeList nodeList;

::grpc::Status
locationservice::SendSystemGpsData(::grpc::ServerContext *context, const ::CommandEx *request, ::GpsData *response) {
    for (auto& node : nodeList) {
        auto &tags = node;
        for (auto tag : tags.second) {
            if (tag->TagType == ProtocolIIOT::GPS) {
                auto m = reinterpret_cast<ProtocolS::GPSTag*>(tag);
                std::cout<<"Gps Request response"<<std::endl;
                response->set_devicedata(m->jsonvalue);
            }
        }
    }

    return grpc::Status::OK;
//    return Service::SendSystemGpsData(context, request, response);
}

locationservice::locationservice(CONNECTION::ConnectionManager *ConnMan) {
    connMan = ConnMan;
}

