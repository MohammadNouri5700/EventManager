//
// Created by aziz on 14.08.21.
//

#include "SnmpProtocol.h"

void ProtocolS::SnMP::SnmpProtocol::Listen()
{
    Run();
}

ProtocolS::SnMP::SnmpProtocol::~SnmpProtocol()
{

}

ProtocolS::SnMP::SnmpProtocol::SnmpProtocol() {}

void ProtocolS::SnMP::SnmpProtocol::Create(Connection *Conn)
{
    (void)Conn; // TODO
    //auto Snmp = reinterpret_cast<ConnectionSnmp*>(Conn); // TODO
    Init();

}
