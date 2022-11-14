//
// Created by aziz on 15.10.21.
//

#include "CoapTag.h"

void ProtocolS::CoapTag::setValue(void *value, size_t Size)
{
    Tag::setValue(value, Size);
}

void ProtocolS::CoapTag::setSubject(ProtocolS::Protocol *subject)
{
    Tag::setSubject(subject);
}

void ProtocolS::CoapTag::SendEvent()
{

}

void ProtocolS::CoapTag::Print()
{
    Tag::Print();
    std::cout<< "Uri : " << URI.Value <<'\n'
             << "Token : " << Token.Value << '\n'
             << "Request : " << Request.Value << '\n';
}

ProtocolS::CoapTag::CoapTag(xmlCoap *node) : Tag(node), URI(node->URI), Token(node->Token), Request(node->Request) {}



void ProtocolS::CoapTag::UpdateValue()
{
    Tag::UpdateValue();
}

ProtocolS::CoapTag::~CoapTag()
{

}

int ProtocolS::CoapTag::GetType()
{
    return 15;
}