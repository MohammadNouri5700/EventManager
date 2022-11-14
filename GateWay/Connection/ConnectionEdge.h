//
// Created by aziz on 20.12.21.
//

#ifndef EVENT_MANAGER_CONNECTIONEDGE_H
#define EVENT_MANAGER_CONNECTIONEDGE_H
#include "Connection.h"

struct xmlEdge : public  xmlNode {
    strTag Func{};
    std::vector<strTag> tags{};
    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    void print() override;

    ~xmlEdge() override;
};

struct ConnectionEdge : public Connection {
    ConnectionEdge();

    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    void NodeSInfo(pugi::xml_node &Node) override;

    void print() override;

    ~ConnectionEdge() override;
};


#endif //EVENT_MANAGER_CONNECTIONEDGE_H
