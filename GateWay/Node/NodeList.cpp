//
// Created by aziz on 03.10.21.
//

#include "NodeList.h"
#include "Tag.h"
#include "../ConvertS/Convert.h"

extern ProtocolS::NodeList nodeList;
extern std::vector<Connection *> ConnectionS;
extern std::vector<Convert> ConvertS;

ProtocolS::Tag *findTag(std::string name)
{
    for (auto p : nodeList)
    {
        for (auto n : p.second)
            if (strcmp(n->Name.Value.c_str(), name.c_str()) == 0)
                return n;
    }
    std::cout << "2Dest Type :" << name.c_str()
              << "Not Found" << std::endl;

    return nullptr;
}

ProtocolIIOT findTagType(std::string name)
{
    for (auto p : nodeList)
        for (auto n : p.second)
            if (strcmp(n->Name.Value.c_str(), name.c_str()) == 0)
                return n->conn->IProtocol;
    std::cout << "1Dest Type :"
              << "Not Found" << std::endl;
    return ProtocolIIOT::ERR;
}

std::string findBaseType(std::string name)
{
    std::string TagName;
    for (auto p : ConvertS)
    {
        std::string a = p.distS()[0];
        if (!strcmp(a.c_str(), name.c_str()))
        {
            TagName = p.source();
            break;
        }
    }
    if (TagName.length() > 2)
        return findTag(TagName)->ValueType.Value;

    std::cout << "1Dest Type :"
              << "Not Found" << std::endl;
    return nullptr;
}



Connection *findConnection(std::string name)
{
    for (auto p : ConnectionS)
    {
            if (strcmp(p->Name.Value.c_str(), name.c_str()) == 0)
            {
                std::cout << "Dest  :" << p->Address.Value.c_str() << std::endl;
                return p;
            }
    }
    std::cout << "3Dest Type :" <<  name.c_str()
              << "Not Found" << std::endl;
    return nullptr;
}
