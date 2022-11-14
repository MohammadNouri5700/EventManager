//
// Created by aziz on 15.09.21.
//

#ifndef XML_CONNECTIONMODBUS_H
#define XML_CONNECTIONMODBUS_H
#include "Connection.h"
#include "../../GrpcServer/modbusservice.h"
//#include "modbusservice.h"
struct xmlModBus:public xmlNode {
    u16Tag StartingAddress{};
    u16Tag NumberOfRegisters{};
    u16Tag Scale{};
    u16Tag Function{};

    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
 

    void print() override;
};

struct ConnectionModbus : public Connection {
    u8Tag SlaveNumber{};
    u8Tag ByteOrder{};
    u8Tag WordOrder{};
    u8Tag RegisterPerMessage{};
    u8Tag CoilPerMessage{};

    void print() override;

    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    ConnectionModbus();

    void NodeSInfo(pugi::xml_node &Node) override;
};


#endif //XML_CONNECTIONMODBUS_H
