#include "nodeservice.h"
#include <iostream>
#include "../GateWay/Node/NodeList.h"
#include "../GateWay/ConvertS/OutputNode.h"
using namespace grpc;
extern std::vector<OutputNode *> OutnodeS;

SystemNodeConfigService::SystemNodeConfigService(CONNECTION::ConnectionManager *ConnMan){
    //connMan = ConnMan;
}

void SystemNodeConfigService::ExtractNodeConfig()
{
    OutputNode *outnode = new OutputNode{};
    for(const NodeData x : nodeData){
        outnode->Conn = findConnection(x.connectionName);
        outnode->ConnectionName.Value = x.connectionName;
        outnode->Name.Value = x.nodeName;
        outnode->Topic.Value = x.Topic;
        outnode->OutputNodeID.Value = x.nodeID;
        outnode->Timer.Value = x.timer;
        std::cout<< "############## " <<  outnode->Conn->Name.Value.c_str() << std::endl;
        
        for(const auto t : x.tagListConfig){
            TagCell *node = new TagCell;
            node->Name = t.TagName;
            node->Alternative = t.Alternative;
            node->att = (t.Attrib ? "public" : "private");
            node->tag = findTag(t.TagName);
            if(!node->tag->OnlyNode)
                node->tag->OnlyNode = (node->att == "public" ? false : true );
            outnode->TagList.push_back(*node);
        }
    }

   
    OutnodeS.push_back(outnode);
    //outnode->async_run((int)(outnode->Timer.Value));
    //outnode->async_run((int)(5)); //To Check Behrang
}

::TagListConfig NodeTagGrpc(const ConfigNodeS::NodeData::TagListConfig nodetag) {
    ::TagListConfig nodeTag;
    nodeTag.Attrib = nodetag.attrib();
    nodeTag.TagName = nodetag.tagname();
    nodeTag.Alternative = nodetag.alternative();
    nodeTag.tag = findTag(nodeTag.TagName);
    
    return nodeTag;
}

::grpc::Status SystemNodeConfigService::SendSystemNodeConfig(::grpc::ServerContext* context, const ::ConfigNodeS* request, ::NodeConfigResponse* response) {


    std::cout << "Received S7 Config request" << std::endl;    
    NodeData tempNodeData;
    nodeData.clear();
    std::cout<< "############## request->plcconfig().size():" << request->nodedata().size() << std::endl;
    for (auto &configNode : request->nodedata()) {
        
        tempNodeData.nodeName = configNode.nodename();
        std::cout<< "############## tempNodeData.nodeName:" << tempNodeData.nodeName << std::endl;
        tempNodeData.connectionName = configNode.connectionname();
        std::cout<< "############## tempNodeData.connectionName:" << tempNodeData.connectionName << std::endl;
        tempNodeData.nodeID = configNode.nodeid();
        tempNodeData.Topic = configNode.topic();
        tempNodeData.timer = configNode.timer();
        for (auto &tag : configNode.taglistconfig()) { 
            tempNodeData.tagListConfig.push_back(NodeTagGrpc(tag));
        }
        nodeData.push_back(tempNodeData);
    }
    ExtractNodeConfig();
    return Status::OK;
}



