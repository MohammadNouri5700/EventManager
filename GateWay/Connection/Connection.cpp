//
// Created by aziz on 14.09.21.
//

#include "Connection.h"

void Connection::print()
{
    std::string strType;
    std::string strProtocol;

    switch (Type) {
    case ConnectionType::RTU :
        strType ="RTU";
        break;
    case ConnectionType::TCP :
        strType = "TCP";
        break;
    case ConnectionType::UDP :
        strType = "UDP";
        break;

    default:
        strType = "ErrType";
        break;
    }

    switch (IProtocol) {
    case ProtocolIIOT::MQTT :
        strProtocol ="MQTT";
        break;
    case ProtocolIIOT::CAN :
        strProtocol ="CAN";
        break;
    case ProtocolIIOT::MODBUS :
        strProtocol = "MODBUS";
        break;
    case ProtocolIIOT::S7 :
        strProtocol = "S7";
        break;
    case ProtocolIIOT::GPS :
        strProtocol = "GPS";
        break;
    case ProtocolIIOT::SNMP :
        strProtocol = "SNMP";
        break;
    case ProtocolIIOT::COAP :
        strProtocol = "COAP";
        break;
    case ProtocolIIOT::EDGE :
        strProtocol = "Edge";
        break;
    default:
        strProtocol = "ErrProtocol";
        break;
    }

    std::cout << std::boolalpha << "( " << strProtocol << " )\n"
              << "Name : " << Name.Value << "\n"
              << "Address : "<< Address.Value << '\n'
              << "Time Out : "<< Timeout.Value << '\n';
}

void Connection::GeneralInfo(pugi::xml_node &General)
{

    Name.Value = General.child("Name").child_value();
    auto address = General.child("address");
    //ConnectionType tc; // TODO: what is it?
    if (!strcmp("CAN", address.attribute("Type").value())) {
        Type = ConnectionType::CAN;
        Address.Value = address.child_value();
    }
    if (!strcmp("GPS", address.attribute("Type").value())) {
        Type = ConnectionType::GPS;
        Address.Value = address.child_value();
    }
    if (!strcmp("TCP", address.attribute("Type").value())) {
        Type = ConnectionType::TCP;
        Address.Value += address.child("IP").child_value();
        std::string p = address.child("Port").child_value();
        Address.Value += p.empty() ? "" : ":"+p ;
    }

    if (!strcmp("RTU", address.attribute("Type").value())) {
        Type = ConnectionType::RTU;
        Address.Value = address.child("Device").child_value();
        std::string p = address.child("Setting").child_value();
        Address.Value += p.empty() ? "" : ":"+p ;
    }

    if (!strcmp("UDP", address.attribute("Type").value())) {
        Type = ConnectionType::UDP;
        Address.Value ="udp://";
        Address.Value += address.child("IP").child_value();
        Address.Value += ":";
        Address.Value += address.child("Port").child_value();
    }

    std::string t =General.child("Timeout").child_value();
    Timeout.Value = t.empty() ? 0 : std::stoull(t);

    std::string DisabledStr = General.child("Disable").child_value();
    if (DisabledStr == "1")
        Disabled = true;
    else
        Disabled = false;
}

void Connection::SetData(pugi::xml_node &connection)
{
    auto General = connection.child("General");
    auto Special = connection.child("Special");
    auto Node = connection.child("Node");


    GeneralInfo(General);
    SpecialInfo(Special);
    NodeSInfo(Node);
}

Connection::~Connection()
{

}

void xmlNode::GeneralInfo(pugi::xml_node &General)
{

    Name.Value = General.child("Name").child_value();
    Units.Value = General.child("Units").child_value();
    std::string str = General.child("ReadWrite").child_value();
    ReadWrite.Value = str.empty() ? 0 :std::stoul(str.c_str());
    str = General.child("Disable").child_value();
    Disable.Value = str.empty() ? 0 :std::stoul(str.c_str());
    str = General.child("Timer").child_value();
    Timer.Value =str.empty() ? 0 :std::stoul(str);
    Notes.Value = General.child("Notes").child_value();
    ValueType.Value = General.child("ValueType").child_value();
}

void xmlNode::print()
{

    std::cout << "Tag \n"
              << "name : " << Name.Value << "\n"
              << "unit : " << Units.Value << "\n"
              << "ReadWrite : " << ReadWrite.Value << "\n"
              << "Disable : " << Disable.Value << "\n"
              << "Timer : " << Timer.Value << "\n"
              << "Notes : " << Notes.Value << "\n"
              << "ValueType : "<< ValueType.Value << "\n";
}

void xmlNode::SetData(pugi::xml_node &Node)
{
    auto General = Node.child("General");
    auto Special = Node.child("Special");

    GeneralInfo(General);
    SpecialInfo(Special);
}

xmlNode::~xmlNode()
{

}
