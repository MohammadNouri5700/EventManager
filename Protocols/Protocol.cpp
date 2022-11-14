//
// Created by aziz on 03.08.21.
//

#include "Protocol.h"
#include "../GateWay/Node/Tag.h"

ProtocolS:: Protocol::Protocol()
{

}

ProtocolS::Protocol::~Protocol()
{

}

void ProtocolS::Protocol::Attach(Tag *tag)
{
    Observer.push_back(tag);
}

void ProtocolS::Protocol::Detach(Tag *tag)
{
    Observer.remove(tag);
}

void ProtocolS::Protocol::UpdateTag(ProtocolS::Tag * tag)
{
    std::cout << "update :"<< tag->strGetName() << std::endl;
}


