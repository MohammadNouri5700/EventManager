//
// Created by aziz on 15.09.21.
//

#include "ConnectionS7.h"
#include "../GateWay/Node/S7Tag.h"
void ConnectionS7::print()
{
    Connection::print();
    std::cout << "Slot Number : " <<SlotNumber.Value << '\n';
    std::cout <<'\n';
    for (auto Tag : NodeS) {
        auto s7 = reinterpret_cast<xmlS7*>(Tag);
        s7->print();
    }
}

void ConnectionS7::SpecialInfo(pugi::xml_node &Special)
{

    std::string str =Special.child("SlotNumber").child_value();
    SlotNumber.Value = (uint8_t)(str.empty() ? 0 : std::stoul(str));
}

void ConnectionS7::SpecialInfoGRPC()
{
}

ConnectionS7::ConnectionS7()
{
    IProtocol = ProtocolIIOT::S7;
}

void ConnectionS7::NodeSInfo(pugi::xml_node &Node)
{
    for (pugi::xml_node Tag: Node.children("Tag")) {
        xmlS7 * n{new xmlS7{}};
        n->SetData(Tag);
        NodeS.push_back(n);
    }
}

void xmlS7::SpecialInfo(pugi::xml_node &Special)
{
    std::string str =Special.child("StartingAddress").child_value();
    StartingAddress.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));
    str =Special.child("BitNumber").child_value();
    BitNumber.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));

    str =Special.child("DBNumber").child_value();
    DBNumber.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));

    str =Special.child("SignalState").child_value();
    SignalState.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));
    std::string TempStr =Special.child("S7TagType").child_value();
    if( !strcmp(TempStr.c_str(),"DATABLOCKTAG" )){
        s7TagType = S7TagType::DATABLOCKTAG;
    }else if( !strcmp(TempStr.c_str(),"IOTAGIN" )){
        s7TagType = S7TagType::IOTAGIN;
    }else if( !strcmp(TempStr.c_str(),"IOTAGOUT" )){
        s7TagType = S7TagType::IOTAGOUT;
    } else if( !strcmp(TempStr.c_str(),"MEMORYTAG" )){
        s7TagType = S7TagType::MEMORYTAG ;
    } else {
        s7TagType = S7TagType::DATABLOCKTAG;
    }
}

void xmlS7::SpecialInfoGRPC()
{
}

void xmlS7::print()
{
    xmlNode::print();
    std::string str = "";
    if (s7TagType == S7TagType::DATABLOCKTAG) {
        str = "DATABLOCKTAG";
    } else if (s7TagType == S7TagType::IOTAGIN) {
       str =  "IOTAGIN" ;
    } else if (s7TagType == S7TagType::IOTAGOUT) {
       str =  "IOTAGOUT" ;
    } else if (s7TagType == S7TagType::MEMORYTAG) {
        str = "MEMORYTAG" ;
    } 
    std::cout << "Starting Address : " << StartingAddress.Value <<"\n"
              << "DB Number : " << DBNumber.Value <<"\n"
              << "Bit Number : " << BitNumber.Value <<"\n"
              << "TagType : " << str <<"\n"
              << "Signal State : " << SignalState.Value <<"\n";
}
