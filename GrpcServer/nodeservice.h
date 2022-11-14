#pragma once

#include "node.grpc.pb.h"
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"


struct OuputNode
{
    std::string tagName;
    std::string tagId;
    std::string serverId;
    bool read;
    bool write;
    int32_t startingAddress;
    int32_t bitNumber;
    int32_t intervalTime;
};

struct TagListConfig
{
    int32_t Attrib;
    std::string TagName;
    std::string Alternative;
    ProtocolS::Tag *tag;
};

struct NodeData
{
    std::string nodeName;
    std::string nodeID;
    std::string connectionName;
    std::string Topic;
    int32_t timer;
    std::vector<TagListConfig> tagListConfig;
};

class SystemNodeConfigService final : public SystemNodeConfig::Service
{
    private:
        std::vector<NodeData> nodeData;
        virtual ::grpc::Status SendSystemNodeConfig(::grpc::ServerContext *context, const ::ConfigNodeS *request, ::NodeConfigResponse *response) override;
        void ExtractNodeConfig();
    public:
        SystemNodeConfigService(CONNECTION::ConnectionManager *ConnMan);
};
