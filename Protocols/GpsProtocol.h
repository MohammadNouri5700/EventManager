//
// Created by aziz on 07.09.21.
//

#ifndef EVENT_MANAGER_GPSPROTOCOL_H
#define EVENT_MANAGER_GPSPROTOCOL_H
#include "Protocol.h"
#include "../W_gps/GpsMessagesParser.h"
#include "../GateWay/Connection/ConnectionGPS.h"
namespace GPs
{
class GpsProtocol: public ProtocolS::Protocol, public GpsMessagesParser
{
public:
    void Listen() override;
    void Create(Connection *Conn) override;
    GpsProtocol(const string &port, unsigned int baudRate);
    GpsProtocol(ConnectionGPS *Conn);

    void UpdateTag(ProtocolS::Tag *tag) override;
};
}


#endif //EVENT_MANAGER_GPSPROTOCOL_H
