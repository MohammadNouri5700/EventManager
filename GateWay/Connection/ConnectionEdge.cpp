//
// Created by aziz on 20.12.21.
//

#include "ConnectionEdge.h"

void xmlEdge::SpecialInfo(pugi::xml_node &Special)
{

    std::string str =Special.child("Func").child_value();
    Func.Value =  str ;

    for (pugi::xml_node Tag: Special.children("tags")) {
        (void)Tag; // TODO ?????
        str = Special.child("T").child_value();
        tags.push_back(strTag{str});
    }


}
void xmlEdge::SpecialInfoGRPC()
{

    //TO DO

}

void xmlEdge::print()
{
    xmlNode::print();
}

xmlEdge::~xmlEdge()
{

}

void ConnectionEdge::SpecialInfo(pugi::xml_node &Special)
{
    (void)Special;//TODO
}

void ConnectionEdge::SpecialInfoGRPC()
{
    //TODO
}

void ConnectionEdge::NodeSInfo(pugi::xml_node &Node)
{
    for (pugi::xml_node Tag: Node.children("Tag")) {
        xmlEdge * n{new xmlEdge{}};
        n->SetData(Tag);
        NodeS.push_back(n);
    }

}

void ConnectionEdge::print()
{
    Connection::print();
}

ConnectionEdge::~ConnectionEdge()
{

}

ConnectionEdge::ConnectionEdge()
{
    IProtocol = ProtocolIIOT::EDGE;
}
