//
// Created by aziz on 15.09.21.
//

#ifndef EVENT_MANAGER_XMLREADER_H
#define EVENT_MANAGER_XMLREADER_H
#include "Connection.h"
#include "ConnectionS7.h"
#include "ConnectionGPS.h"
#include "ConnectionMqtt.h"
#include "ConnectionSnmp.h"
#include "ConnectionModbus.h"
#include "ConnectionCoap.h"
#include "ConnectionEdge.h"
#include "ConnectionCan.h"
#include "xmlnetwork.h"
#include <vector>

#include "../ConvertS/Convert.h"
#include  "../ConvertS/OutputNode.h"
class XmlReader
{
    pugi::xml_document xmlDoc{};
public:
    XmlReader();
    bool setFile(std::string Name);
    void ExtraConnection(std::vector<Connection*>& conn);
    void ExtraConvert(std::vector<Convert>& con, const std::vector<Connection*> &conn);
    void ExtraOutputNode(std::vector<OutputNode*> &outnode);
    void ExtraNetwork(Network& network);
};




#endif //EVENT_MANAGER_XMLREADER_H
