//
// Created by aziz on 07.09.21.
//

#include "GpsProtocol.h"

void GPs::GpsProtocol::Listen()
{
    thrdFetchNMEAHandler();
}

GPs::GpsProtocol::GpsProtocol(const string &port, unsigned int baudRate) : GpsMessagesParser(port, baudRate) {}

void GPs::GpsProtocol::Create(Connection *Conn)
{
    (void)Conn;//TODO
}

GPs::GpsProtocol::GpsProtocol(ConnectionGPS *Conn): GpsMessagesParser(Conn->Address.Value, 9600)
{

}

void GPs::GpsProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}
