//
// Created by aziz on 15.09.21.
//

#include "ConnectionCan.h"


void ConnectionCAN::print()
{
    Connection::print();
    
    for (auto Tag : NodeS) {
        auto CAN = reinterpret_cast<xmlCAN*>(Tag);
        CAN->print();
    }
}

void ConnectionCAN::SpecialInfo(pugi::xml_node &Special)
{
    std::string str = Special.child("BitRate").child_value();
    BitRate.Value = (uint32_t)(str.empty() ? 0 : std::stoul(str));

    
}

void ConnectionCAN::SpecialInfoGRPC()
{

}

ConnectionCAN::ConnectionCAN()
{
    IProtocol = ProtocolIIOT::CAN;
}

void ConnectionCAN::NodeSInfo(pugi::xml_node &Node)
{
    for (pugi::xml_node Tag: Node.children("Tag")) {
        xmlCAN * n{new xmlCAN{}};
        n->SetData(Tag);
        NodeS.push_back(n);
    }
}

strTag ConnectionCAN::getID() {
    return ID;
}

void xmlCAN::SpecialInfo(pugi::xml_node &Special)
{
    std::string str =Special.child("StartingAddress").child_value();
    StartingAddress.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));
    str =Special.child("BitNumber").child_value();
    BitNumber.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));
    str =Special.child("CANID").child_value();
    CANID.Value = (uint32_t)(str.empty() ? 0 : std::stoul(str));
    str =Special.child("BitCount").child_value();
    BitCount.Value = (uint32_t)(str.empty() ? 0 : std::stoul(str));
}

void xmlCAN::SpecialInfoGRPC()
{
}


void xmlCAN::print()
{
    xmlNode::print();
    std::cout << "CANID : " << CANID.Value << '\n';
    std::cout << "BitNumber : " << BitNumber.Value << '\n';
    std::cout << "BitCount : " << BitCount.Value << '\n';
    std::cout << "StartingAddress : " << StartingAddress.Value << '\n';
}
