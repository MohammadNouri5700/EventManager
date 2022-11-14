//
// Created by aziz on 15.09.21.
//

#ifndef XML_CONNECTIONCAN_H
#define XML_CONNECTIONCAN_H
#include "Connection.h"
//#include "../../GrpcServer/CANservice.h"

using bTage = XmlTag<bool>;


struct xmlCAN : public  xmlNode {
    u16Tag StartingAddress{};
    u16Tag BitNumber{};
    u32Tag CANID{};
    u16Tag BitCount{};

    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    void print() override;
};


struct ConnectionCAN : public Connection {
    strTag ID{};
    //u32Tag CANID{};
    u32Tag BitRate{};
    
    void print() override;

    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    void NodeSInfo(pugi::xml_node &Node) override;

    strTag getID();

    ConnectionCAN();
};


#endif //XML_CONNECTIONCAN_H
