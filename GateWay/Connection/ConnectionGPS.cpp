//
// Created by aziz on 18.09.21.
//

#include "ConnectionGPS.h"

void ConnectionGPS::SpecialInfo(pugi::xml_node &Special)
{
    (void)Special; // TODO
}

void ConnectionGPS::SpecialInfoGRPC()
{
 // TODO
}

void ConnectionGPS::print()
{
    Connection::print();
}

ConnectionGPS::ConnectionGPS()
{
    IProtocol = ProtocolIIOT::GPS;
}
