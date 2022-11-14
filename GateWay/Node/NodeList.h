//
// Created by aziz on 03.10.21.
//

#ifndef EVENT_MANAGER_NODELIST_H
#define EVENT_MANAGER_NODELIST_H
#include "Tag.h"




namespace ProtocolS
{
using Node = std::pair<std::string, std::vector<Tag*>>;
using NodeList = std::list<Node>;
}
extern ProtocolS::NodeList nodeList;

ProtocolS::Tag * findTag(std::string name);
ProtocolIIOT findTagType(std::string name);
Connection * findConnection(std::string name);
std::string findBaseType(std::string name);
#endif //EVENT_MANAGER_NODELIST_H
