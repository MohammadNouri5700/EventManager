//
// Created by aziz on 18.09.21.
//

#include "ConnectionGPS.h"

void ConnectionGPS::SpecialInfo(pugi::xml_node &Special)
{
    // (void)Special; // TODO
}

void ConnectionGPS::SpecialInfoGRPC()
{
 // TODO
}

void ConnectionGPS::print()
{
    Connection::print();
}

void ConnectionGPS::NodeSInfo(pugi::xml_node &Node)
{
    for (pugi::xml_node Tag: Node.children("Tag")) {
        xmlGPS * n{new xmlGPS{}};
        n->SetData(Tag);
        NodeS.push_back(n);
    }
}

ConnectionGPS::ConnectionGPS()
{
    IProtocol = ProtocolIIOT::GPS;
}

void xmlGPS::SpecialInfo(pugi::xml_node & Special)
{


}

void xmlGPS::SpecialInfoGRPC()
{
    
}

void xmlGPS::print()
{

}
