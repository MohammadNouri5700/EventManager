//
// Created by aziz on 15.10.21.
//

#ifndef EVENT_MANAGER_CONNECTIONCOAP_H
#define EVENT_MANAGER_CONNECTIONCOAP_H
#include "Connection.h"

struct xmlCoap : public  xmlNode {
    strTag URI{};
    strTag Token{};
    strTag Request{};
    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() ;
    void print() override;
};

struct  ConnectionCoap :public Connection {
    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override{};
    void NodeSInfo(pugi::xml_node &Node) override;

    void print() override;

    ConnectionCoap();
};


#endif //EVENT_MANAGER_CONNECTIONCOAP_H
