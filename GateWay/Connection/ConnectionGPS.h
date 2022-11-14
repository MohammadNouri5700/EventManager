//
// Created by aziz on 18.09.21.
//

#ifndef EVENT_MANAGER_CONNECTIONGPS_H
#define EVENT_MANAGER_CONNECTIONGPS_H
#include "Connection.h"

struct ConnectionGPS: public Connection {
public:
    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    void print() override;

    ConnectionGPS();
};


#endif //EVENT_MANAGER_CONNECTIONGPS_H
