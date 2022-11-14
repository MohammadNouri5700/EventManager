#pragma once

#include "s7.grpc.pb.h"
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"


struct SnapSevenTag
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

 struct SnapSevenIoTag{
    std::string tagName;
    std::string tagId;
    std::string tagType;
    std::string ioType;
    int32_t wordCount;
    int32_t bitCount;
    int32_t byteCount;
};
struct SnapSevenDataBlockTag{
            std::string tagName;
            std::string tagId;
            std::string functionCode;
            int32_t count;
            ParameterDataType parameter;
            int32_t startAddress;
            int32_t bitNumber;
            int32_t dbNumber;
};
struct PlcConfig
{
    std::string plcName;
    std::string plcID;
    std::string plcAddress;
    int32_t plcPort;
    int32_t plcSlot;
    std::vector<SnapSevenDataBlockTag> dataBlockTag;
    std::vector<SnapSevenIoTag> ioTag;
};
class SystemSnapSevenConfigService final : public SystemSnapSevenConfig::Service
{
    private:
        CONNECTION::ConnectionManager *connMan;
        std::vector<PlcConfig> plcConfig;
        virtual ::grpc::Status SendSystemSnapSevenConfig(::grpc::ServerContext *context, const ::ConfigSnapSeven *request, ::SnapSevenConfigResponse *response) override;
        void ExtractSnap7Config();
    public:
        SystemSnapSevenConfigService(CONNECTION::ConnectionManager *ConnMan);
};
