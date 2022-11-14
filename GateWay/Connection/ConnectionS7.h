//
// Created by aziz on 15.09.21.
//

#ifndef XML_CONNECTIONS7_H
#define XML_CONNECTIONS7_H
#include "Connection.h"
enum S7TagType {
        DATABLOCKTAG=0,
        IOTAGOUT=1,
        IOTAGIN=2,
        MEMORYTAG=3
    } ;
struct xmlS7: public xmlNode {
    u16Tag StartingAddress{};
    u16Tag BitNumber{};
    u16Tag DBNumber{};
    bTag SignalState{};
    S7TagType s7TagType{};
    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    void print() override;
};

struct ConnectionS7: public Connection {
    u8Tag SlotNumber{};
    void print() override;

    void NodeSInfo(pugi::xml_node &Node) override;
    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    ConnectionS7();
};
#endif //XML_CONNECTIONS7_H
