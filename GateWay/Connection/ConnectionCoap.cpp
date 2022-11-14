//
// Created by aziz on 15.10.21.
//

#include "ConnectionCoap.h"

void xmlCoap::SpecialInfo(pugi::xml_node &Special)
{
    URI.Value = Special.child("URI").child_value();
    Token.Value = Special.child("Token").child_value();
    Request.Value = Special.child("Request").child_value();

}

void xmlCoap::print()
{
    xmlNode::print();
    std::cout<< "Uri : " << URI.Value <<'\n'
             << "Token : " << Token.Value << '\n'
             << "Request : " << Request.Value << '\n';
}

void ConnectionCoap::SpecialInfo(pugi::xml_node &Special)
{
    (void)Special; //TODO
}

void xmlCoap::SpecialInfoGRPC()
{
     //TODO
}

void ConnectionCoap::NodeSInfo(pugi::xml_node &Node)
{
    for (pugi::xml_node Tag: Node.children("Tag")) {
        xmlCoap * n{new xmlCoap{}};
        n->SetData(Tag);
        NodeS.push_back(n);
    }
}

void ConnectionCoap::print()
{
    Connection::print();


    for (auto Tag : NodeS) {
        reinterpret_cast<xmlCoap*>(Tag)->print();
    }

}

ConnectionCoap::ConnectionCoap()
{
    IProtocol = ProtocolIIOT::COAP;
}
