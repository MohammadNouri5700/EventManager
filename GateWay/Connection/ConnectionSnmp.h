//
// Created by aziz on 18.09.21.
//

#ifndef EVENT_MANAGER_CONNECTIONSNMP_H
#define EVENT_MANAGER_CONNECTIONSNMP_H
#include "Connection.h"

class ConnectionSnmp: public Connection
{
public:
    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    void print() override;
    ConnectionSnmp();
};


#endif //EVENT_MANAGER_CONNECTIONSNMP_H
