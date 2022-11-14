//
// Created by aziz on 13.12.21.
//

#include "MouseProtocol.h"

ProtocolS::MOUSE::MouseProtocol::~MouseProtocol()
{

}

void ProtocolS::MOUSE::MouseProtocol::Listen()
{
    mouse::loop();
}

void ProtocolS::MOUSE::MouseProtocol::Create(Connection *Conn)
{
    (void)Conn;//TODO
}

void ProtocolS::MOUSE::MouseProtocol::Open(Connection *Conn)
{

}

void ProtocolS::MOUSE::MouseProtocol::Close()
{

}

void ProtocolS::MOUSE::MouseProtocol::KeepAlive()
{

}

bool ProtocolS::MOUSE::MouseProtocol::isOK()
{
    return false;
}

void ProtocolS::MOUSE::MouseProtocol::Reconnect()
{

}

void ProtocolS::MOUSE::MouseProtocol::hasError()
{

}

void ProtocolS::MOUSE::MouseProtocol::DataReceived()
{

}

ProtocolS::MOUSE::MouseProtocol::MouseProtocol():mouse() {}

void ProtocolS::MOUSE::MouseProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}

