//
// Created by aziz on 15.09.21.
//

#include "ConnectionModbus.h"

void ConnectionModbus::print()
{
    Connection::print();
    std::cout << "Slave Number : " <<  SlaveNumber.Value << '\n'
              << "Byte order : "	 <<   ByteOrder.Value << '\n'
              <<"Word order"	<< WordOrder.Value <<'\n'
              << "Register per message : " << RegisterPerMessage.Value << '\n'
              << "Coil per Message : " << CoilPerMessage.Value << '\n';
    for (auto Tag : NodeS) {
        auto mqtt = reinterpret_cast<xmlModBus*>(Tag);
        mqtt->print();
    }

}

void ConnectionModbus::SpecialInfo(pugi::xml_node &Special)
{

    std::string str;
    str = Special.child("SlaveNumber").child_value();
    SlaveNumber.Value = (uint8_t)(str.empty() ? 0 :std::stoi(str));
    str = Special.child("ByteOrder").child_value();
    ByteOrder.Value= (uint8_t)(str.empty() ? 0 :std::stoi(str));
    str = Special.child("WordOrder").child_value();
    WordOrder.Value= (uint8_t)(str.empty() ? 0 :std::stoi(str));
    str = Special.child("RegisterPerMessage").child_value();
    RegisterPerMessage.Value= (uint8_t)(str.empty() ? 0 :std::stoi(str));
    str = Special.child("CoilPerMessage").child_value();
    CoilPerMessage.Value= (uint8_t)(str.empty() ? 0 :std::stoi(str));
}
void ConnectionModbus::SpecialInfoGRPC()
{

    
}


ConnectionModbus::ConnectionModbus()
{
    IProtocol = ProtocolIIOT::MODBUS;
}

void ConnectionModbus::NodeSInfo(pugi::xml_node &Node)
{
    for (pugi::xml_node Tag: Node.children("Tag")) {
        xmlModBus * n{new xmlModBus{}};
        n->SetData(Tag);
        NodeS.push_back(n);
    }
}

void xmlModBus::SpecialInfo(pugi::xml_node &Special)
{
    StartingAddress.Value = (uint16_t)std::stoul(Special.child("StartingAddress").child_value());
    NumberOfRegisters.Value = (uint8_t)std::stoul(Special.child("NumberOfRegisters").child_value());
    Scale.Value = (uint16_t)std::stoul(Special.child("Scale").child_value());
    Function.Value = (uint8_t)std::stoul(Special.child("Function").child_value());
} 

void xmlModBus::SpecialInfoGRPC()
{
    
}


void xmlModBus::print()
{
    xmlNode::print();
    std::cout << "Starting Address :" << StartingAddress.Value <<"\n"
              << "Number Of Registers :" << NumberOfRegisters.Value <<"\n"
              << "Scale : " << Scale.Value <<"\n"
              << "Function : " << Function.Value <<"\n";
}
