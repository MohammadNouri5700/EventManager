//
// Created by aziz on 17.10.21.
//

#include "CoapProtocol.h"


void ProtocolS::COAP::CoapProtocol::Listen()
{
    CoAP::CoapNode::Run();
}

void ProtocolS::COAP::CoapProtocol::Create(Connection *Conn)
{
    (void)Conn;//TODO
}

void ProtocolS::COAP::CoapProtocol::Open(Connection *Conn)
{

}

void ProtocolS::COAP::CoapProtocol::Close()
{

}

void ProtocolS::COAP::CoapProtocol::KeepAlive()
{

}

bool ProtocolS::COAP::CoapProtocol::isOK()
{
    return false;
}

void ProtocolS::COAP::CoapProtocol::Reconnect()
{

}

void ProtocolS::COAP::CoapProtocol::hasError()
{

}

void ProtocolS::COAP::CoapProtocol::DataReceived()
{

}

ProtocolS::COAP::CoapProtocol::~CoapProtocol()
{

}

void ProtocolS::COAP::CoapProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}

void ProtocolS::COAP::CoapProtocol::Write(Data* data,Tag* tag)
{
    Protocol::Write(data,tag);
}
