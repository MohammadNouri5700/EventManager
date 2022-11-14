//
// Created by aziz on 13.12.21.
//

#include "KeyProtocol.h"

ProtocolS::KEY::KeyProtocol::~KeyProtocol()
{

}

void ProtocolS::KEY::KeyProtocol::Listen()
{
    key::loop();
}

void ProtocolS::KEY::KeyProtocol::Create(Connection *Conn)
{
    (void)Conn;//TODO
}

void ProtocolS::KEY::KeyProtocol::Open(Connection *Conn)
{

}

void ProtocolS::KEY::KeyProtocol::Close()
{

}

void ProtocolS::KEY::KeyProtocol::KeepAlive()
{

}

bool ProtocolS::KEY::KeyProtocol::isOK()
{
    return false;
}

void ProtocolS::KEY::KeyProtocol::Reconnect()
{

}

void ProtocolS::KEY::KeyProtocol::hasError()
{

}

void ProtocolS::KEY::KeyProtocol::DataReceived()
{

}

ProtocolS::KEY::KeyProtocol::KeyProtocol():key() {}

void ProtocolS::KEY::KeyProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}
