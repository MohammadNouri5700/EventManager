//
// Created by aziz on 19.12.21.
//

#include "CentralProtocol.h"

ProtocolS::CentralProtocol::~CentralProtocol()
{

}

void ProtocolS::CentralProtocol::Listen()
{

}

void ProtocolS::CentralProtocol::Create(Connection *Conn)
{
    (void)Conn;//TODO
}

void ProtocolS::CentralProtocol::Open(Connection *Conn)
{

}

void ProtocolS::CentralProtocol::Close()
{

}

void ProtocolS::CentralProtocol::KeepAlive()
{

}

bool ProtocolS::CentralProtocol::isOK()
{
    return false;
}

void ProtocolS::CentralProtocol::Reconnect()
{

}

void ProtocolS::CentralProtocol::hasError()
{

}

void ProtocolS::CentralProtocol::DataReceived()
{

}

void ProtocolS::CentralProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}

void ProtocolS::CentralProtocol::Write(Data* data,Tag* tag)
{
    Protocol::Write(data,tag);
}
