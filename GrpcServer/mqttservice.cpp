#include "mqttservice.h"
#include "mqttclient.h"


#include "../Protocols/SubscriberProtocol.h"
#include "../GateWay/Connection/ConnectionMqtt.h"
#include "../GateWay/Node/NodeList.h"
#include "../GateWay/Node/MqttTag.h"

using namespace grpc;
using namespace std;
extern std::vector<Connection *> ConnectionS;

// mosqpp::ClientTag ClientTagsFromGrpc(const MqttClients::MqttClient::ClientTag& tag) {
//     mosqpp::ClientTag clientTag;
//     clientTag.tagName = tag.tagname();
//     clientTag.topicName = tag.topicname();
//     clientTag.mqttVarType = (mosqpp::MqttVarType)tag.mqttvartype();
//     clientTag.onOff = tag.onoff();
//     clientTag.systemName = tag.systemname();
//     clientTag.clientActions = (mosqpp::ClientActions)tag.clientactions();
//     return clientTag;
// }

MqttClientsConfigService::MqttClientsConfigService(CONNECTION::ConnectionManager *ConnMan){
        connMan = ConnMan;
}

void MqttClientsConfigService::ExtractMqttClientConfig() {
    ConnectionMqtt *mqtt = new ConnectionMqtt{};
    for(const MqttClient x : mqttClients){
        mqtt->IProtocol = ProtocolIIOT::MQTT;
        mqtt->Address.Value  = x.hostAddress + ":" + std::to_string(x.hostPort); 
        std::cout<< "############## Address.Value" << mqtt->Address.Value.c_str() << std::endl;
        mqtt->Name.Value = x.clientName;
        std::cout<< "############## Name.Value" << mqtt->Name.Value.c_str() << std::endl;
        mqtt->Timeout.Value = x.timeOut;
        mqtt->ID.Value = x.clientID;
        mqtt->iMaxMessageSize.Value = x.business.size;
        mqtt->iTps.Value = x.business.trpersec;
        

    // mqtt-> Protocol = x.hostAddress ;
    // mqtt-> Username = x.hostAddress ;
    // mqtt-> Password = x.hostAddress ;
    // mqtt-> ReconnectPeriod = x.hostAddress ;
    // mqtt-> ConnectTimeout = x.hostAddress ;
    // mqtt-> KeepAlive = x.hostAddress ;
    // mqtt-> WillTopic = x.hostAddress ;
    // mqtt-> WillQoS = x.hostAddress ;
    // mqtt-> WillRetain = x.hostAddress ;
    // //AppendTimestamp;
    // mqtt-> CleanSession = x.hostAddress ;
    // mqtt-> ReschedulePings = x.hostAddress ;
    // //u8Tag MQTTv3_1_compliant;
    // mqtt-> WillPayload = x.hostAddress ;
    // mqtt-> QoSZero = x.hostAddress ;
    // mqtt-> ExecutionRetry = x.hostAddress ;
    // mqtt-> RetryInterval = x.hostAddress ;
    // mqtt-> RetriesIntervalUnit = x.hostAddress ;

        for(const auto t : x.clientTag){
            xmlMqtt *node = new xmlMqtt;
            node->Name.Value = t.tagName;
            node->Topic.Value = t.topicName;
            node->clientAction = t.clientActions;
            node->ValueType.Value = "Json";
            

            mqtt->NodeS.push_back(node);
        }
        
    }


    std::cout << "config MQTT" << std::endl;
    auto m = reinterpret_cast<ConnectionMqtt *>(mqtt);
    ProtocolS::Mqtt::SubscriberProtocol *node{new ProtocolS::Mqtt::SubscriberProtocol{m}};
    //node->setErrCallBack(errHandMqtt);
    //node->SetHandler(cb_lose, false);
    for (auto& node : nodeList) {
        int Counter  = 0;    
        auto &tags = node;
        for (auto tag : tags.second) {
            if (tag->TagType == ProtocolIIOT::MQTT) {
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
        auto mq = reinterpret_cast<xmlMqtt *>(t);
        ProtocolS::MqttTag *mn{new ProtocolS::MqttTag(mq)};
        mn->conn = m;
        n.second.push_back(mn);
    }
    nodeList.push_back(std::move(n));

    for (auto [i, n] : nodeList)
    {
        if (strcmp(i.c_str(), m->Name.Value.c_str()) == 0)
            for (auto t : n)
            {
                t->setSubject(node);
                t->TagType = ProtocolIIOT::MQTT;
            }
    };
    ConnectionS.push_back(mqtt);
    connMan->AddConnection(node);
}

::ClientTag MqttClientTagGRPC(const MqttClients::MqttClient::ClientTag clnttag) {
    ::ClientTag clientTag;

    clientTag.tagName = clnttag.tagname();
    clientTag.topicName = clnttag.topicname();
    std::cout << "########## clnttag.topicname();"<<  clnttag.topicname() << std::endl;    
    clientTag.mqttVarType = clnttag.mqttvartype();
    std::cout << "########## clientTag.mqttVarType();"<<  clientTag.mqttVarType << std::endl;    
    clientTag.onOff = clnttag.onoff();
    clientTag.systemName = clnttag.systemname();
    clientTag.clientActions = clnttag.clientactions();
    return clientTag;
}


::grpc::Status MqttClientsConfigService::SendMqttClientsConfig(::grpc::ServerContext* context, const ::MqttClients* request, ::ConfigResponse* response) {
    std::cout << "Received MqttClientsConfig request" << std::endl;

    std::cout<< "############## request->mqttclient().size():" << request->mqttclient().size() << std::endl;
    mqttClients.clear();
    for (auto &configmqttclient : request->mqttclient()) {
        
        MqttClient tempMqttClient;
        tempMqttClient.clientName = configmqttclient.clientname();
        std::cout<< "############## tempMqttClient.clientName:" << tempMqttClient.clientName << std::endl;
        tempMqttClient.hostAddress = configmqttclient.hostaddress();
        std::cout<< "############## tempMqttClient.hostAddress:" << tempMqttClient.hostAddress << std::endl;
        tempMqttClient.clientID = configmqttclient.clientid();
        tempMqttClient.hostPort = configmqttclient.hostport();
        tempMqttClient.business.size = configmqttclient.business().size();
        tempMqttClient.business.trpersec = configmqttclient.business().trpersec();
        for (auto &tag : configmqttclient.clienttag()) { 
            std::cout<< "############## tempPlcConfig.DB Tag"  << std::endl;
            tempMqttClient.clientTag.push_back(MqttClientTagGRPC(tag));
        }
        mqttClients.push_back(tempMqttClient);
    }

    ExtractMqttClientConfig();
    return Status::OK;

    response->set_success(true);
    response->set_errorcode(0);
    response->set_errordesc("success");
    return Status::OK;
}

::grpc::Status MqttBrokerConfigService::SendMqttBrokerConfig(::grpc::ServerContext* context, const ::MqttBorker* request, ::ConfigResponse* response)  {
    std::cout << "I 'm here ..." << std::endl;
    return Status::OK;

}
