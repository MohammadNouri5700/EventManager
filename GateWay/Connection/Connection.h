//
// Created by aziz on 14.09.21.
//

#ifndef XML_CONNECTION_H
#define XML_CONNECTION_H
#include <pugixml.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <map>
#include <vector>
#include "XmlTag.h"
//#include "../../GrpcServer/modbusservice.h"

enum class ProtocolIIOT
{
    ERR = 0,
    MQTT = 1,
    S7 = 2,
    MODBUS = 3,
    GPS = 4,
    SNMP = 5,
    COAP = 6,
    EDGE = 7,
    CAN = 8
};
enum class ConnectionType
{
    ERR,
    TCP,
    RTU,
    UDP,
    CAN
};

using strTag = XmlTag<std::string>;
using bTag = XmlTag<bool>;
using u16Tag = XmlTag<uint16_t>;
using u32Tag = XmlTag<uint32_t>;
using u8Tag = XmlTag<uint8_t>;
using FloatTag = XmlTag<float>;
using Second = XmlTag<size_t>;

struct xmlNode
{
    strTag Name{};
    strTag Units{};
    strTag ValueType{};
    strTag Notes{};
    bTag ReadWrite{0};
    bTag Disable{0};
    Second Timer{};

    void GeneralInfo(pugi::xml_node &General);
    virtual void SpecialInfo(pugi::xml_node &Special) = 0;
    virtual void SpecialInfoGRPC() = 0;
    virtual void print();
    void SetData(pugi::xml_node &connection);

    virtual ~xmlNode();
};
struct Connection
{
    ProtocolIIOT IProtocol{};
    strTag Address{};
    ConnectionType Type{};
    strTag Name{};
    Second Timeout{};
    std::vector<xmlNode *> NodeS{};
    FloatTag iTps;
    bool Disabled;
    u16Tag iMaxMessageSize ;
    void GeneralInfo(pugi::xml_node &General);
    virtual void SpecialInfo(pugi::xml_node &Special) = 0;
    virtual void NodeSInfo(pugi::xml_node &Node) = 0;
    virtual void SpecialInfoGRPC() = 0;
    virtual void print();
    void AllPrint();
    void SetData(pugi::xml_node &connection);

    virtual ~Connection();
};

#endif // XML_CONNECTION_H
