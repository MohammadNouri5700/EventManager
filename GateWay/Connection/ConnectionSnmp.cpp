//
// Created by aziz on 18.09.21.
//

#include "ConnectionSnmp.h"

void ConnectionSnmp::SpecialInfo(pugi::xml_node &Special)
{
    (void)Special; // TODO
}

void ConnectionSnmp::SpecialInfoGRPC()
{
     // TODO
}

void ConnectionSnmp::print()
{
    Connection::print();
}

ConnectionSnmp::ConnectionSnmp()
{
    IProtocol = ProtocolIIOT::SNMP;
}
