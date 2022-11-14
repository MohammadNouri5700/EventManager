#include "mqttpodservice.h"

using namespace grpc;
using namespace std;

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
::grpc::Status MqttPodNodeConfigService::SendMqttPodNodeConfig(::grpc::ServerContext* context, const ::MqttPodNode* request, ::PodResponse* response) {
    std::cout << "Received MqttpodClientsConfig request" << std::endl;
   
    response->set_success(true);
    response->set_errorcode(0);
    response->set_errordesc("success");
    
    return Status::OK;
}
