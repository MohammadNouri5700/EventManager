#include "s7service.h"
#include <iostream>
#include "../Protocols/S7Protocol.h"
#include "../GateWay/Connection/ConnectionS7.h"
#include "../GateWay/Node/NodeList.h"
#include "../GateWay/Node/S7Tag.h"
using namespace grpc;
extern std::vector<Connection *> ConnectionS;
std::map<ParameterDataType, std::string> ParameterDataTypeToStringMap;

SystemSnapSevenConfigService::SystemSnapSevenConfigService(CONNECTION::ConnectionManager *ConnMan){
    connMan = ConnMan;
    ParameterDataTypeToStringMap[BOOLEAN] = "bool";
    ParameterDataTypeToStringMap[INT8];
    ParameterDataTypeToStringMap[UINT8];
    ParameterDataTypeToStringMap[INT16] = "int16";
    ParameterDataTypeToStringMap[UINT16];
    ParameterDataTypeToStringMap[INT32] = "int";
    ParameterDataTypeToStringMap[UINT32];
    ParameterDataTypeToStringMap[INT64];
    ParameterDataTypeToStringMap[UINT64];
    ParameterDataTypeToStringMap[FLOAT32] = "float";
    ParameterDataTypeToStringMap[FLOAT64];
    ParameterDataTypeToStringMap[STRING];
}


void SystemSnapSevenConfigService::ExtractSnap7Config()
{
    ConnectionS7 *snap7 = new ConnectionS7{};
    for(const PlcConfig x : plcConfig){
        snap7->IProtocol = ProtocolIIOT::S7;
        snap7->Address.Value = x.plcAddress ;//+ ":" + x.plcPort;
        std::cout<< "############## " << snap7->Address.Value.c_str() << std::endl;
        snap7->SlotNumber.Value = 2;

        for(const auto t : x.dataBlockTag){
            xmlS7 *node = new xmlS7;
            node->Name.Value = t.tagName;
            node->BitNumber.Value = t.bitNumber;
            node->DBNumber.Value = t.dbNumber;
            node->StartingAddress.Value = t.startAddress;
            node->ValueType.Value = ParameterDataTypeToStringMap[t.parameter];
            std::cout<< "############## " << t.tagName << std::endl;
            snap7->NodeS.push_back(node);
        }
        for(const auto t : x.ioTag){
            xmlS7 *node = new xmlS7;
            node->Name.Value = t.tagName;
            node->BitNumber.Value = t.bitCount;
            node->StartingAddress.Value = t.wordCount;
            node->ValueType.Value = t.tagType;
            snap7->NodeS.push_back(node);
        }
    }

    auto m = reinterpret_cast<ConnectionS7 *>(snap7);
    m->Name.Value = (*plcConfig.begin()).plcName;
    ProtocolS::S7::S7Protocol *s7{new ProtocolS::S7::S7Protocol};
    s7->Create(m);
    for (auto& node : nodeList) {
        int Counter  = 0;    
        auto &tags = node;
        for (auto tag : tags.second) {
            if (tag->TagType == ProtocolIIOT::S7) {
                std::cout << tag->strGetName() << "Found Tag to Delete" << Counter << std::endl;
                tags.second.clear();
            }
            Counter ++; 
        }
        std::cout << "tag Deleted : " << tags.second.size() << std::endl;
    }

    ProtocolS::Node n;
    n.first = m->Name.Value;
    for (auto t : m->NodeS)
    {
        auto mq = reinterpret_cast<xmlS7 *>(t);
        ProtocolS::S7Tag *mn{new ProtocolS::S7Tag(mq)};
        mn->TagType = ProtocolIIOT::S7;
        n.second.push_back(mn);
    }
    nodeList.push_back(std::move(n));
    for (auto& [i, n] : nodeList)
    {
        if (strcmp(i.c_str(), m->Name.Value.c_str()) == 0) {
            std::cerr << "i.c_str()" << i.c_str()  << "m->Name.Value.c_str()" << m->Name.Value.c_str() << std::endl ;
            for (auto t : n)
            {
                t->setSubject(s7);
                t->conn = m;
                t->TagType = ProtocolIIOT::S7;
                t->Timer.Value = 1;
            }
        }
    };
    ConnectionS.push_back(snap7);
    connMan->AddConnection(s7);
}


::SnapSevenIoTag SnapSevenIOTagGrpc(const ConfigSnapSeven::PLCConfig::IoTag iotag) {
    ::SnapSevenIoTag ioTag;
    ioTag.tagName = iotag.tagname();
    ioTag.tagId = iotag.tagid();
    ioTag.tagType = iotag.tagtype();
    //ioTag.wordCount = iotag.wordcount();
    //ioTag.bitCount = iotag.bitcount();
    ioTag.byteCount = iotag.bytecount();
    return ioTag;
}

::SnapSevenDataBlockTag SnapSevenDataBlockTagGRPC(const ConfigSnapSeven::PLCConfig::DataBlockTag dbtag) {
    ::SnapSevenDataBlockTag dataBlockTag;
    dataBlockTag.tagName = dbtag.tagname();
    dataBlockTag.tagId = dbtag.tagid();
    dataBlockTag.startAddress = dbtag.startaddress();
    std::cout << "########## dbtag.startaddress();"<<dbtag.startaddress() << std::endl;    
    dataBlockTag.dbNumber = dbtag.dbnumber();
    std::cout << "########## dbtag.dbnumber()"<<dbtag.dbnumber() << std::endl;    
    dataBlockTag.functionCode = dbtag.functioncode();
    dataBlockTag.bitNumber = dbtag.bitnumber();
    dataBlockTag.parameter = dbtag.parameter();
    //dataBlockTag.count = dbtag.count();
    return dataBlockTag;
}

::grpc::Status SystemSnapSevenConfigService::SendSystemSnapSevenConfig(::grpc::ServerContext* context, const ::ConfigSnapSeven* request, ::SnapSevenConfigResponse* response) {


    std::cout << "Received S7 Config request" << std::endl;    
    PlcConfig tempPlcConfig;
    plcConfig.clear();
    std::cout<< "############## request->plcconfig().size():" << request->plcconfig().size() << std::endl;
    for (auto &configSnapSeven : request->plcconfig()) {
        
        tempPlcConfig.plcName = configSnapSeven.plcname();
        std::cout<< "############## tempPlcConfig.plcName:" << tempPlcConfig.plcName << std::endl;
        tempPlcConfig.plcAddress = configSnapSeven.plcaddress();
        std::cout<< "############## tempPlcConfig.plcAddress:" << tempPlcConfig.plcAddress << std::endl;
        tempPlcConfig.plcID = configSnapSeven.plcid();
        tempPlcConfig.plcPort = configSnapSeven.plcport();
        for (auto &tag : configSnapSeven.iotag()) { 
            tempPlcConfig.ioTag.push_back(SnapSevenIOTagGrpc(tag));
        }
        for (auto &tag : configSnapSeven.datablocktag()) { 
            std::cout<< "############## tempPlcConfig.DB Tag"  << std::endl;
            tempPlcConfig.dataBlockTag.push_back(SnapSevenDataBlockTagGRPC(tag));
        }
        
        plcConfig.push_back(tempPlcConfig);
    }
    
    if(request->plcconfig().size() > 0)
        ExtractSnap7Config();
    return Status::OK;
}



