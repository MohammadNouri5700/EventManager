#pragma once

#include "mqtt.grpc.pb.h"
#include "../GateWay/Connection/Connection.h"
#include "../ConnectionManager/ConnectionManager.h"

namespace mosqpp
{
    class mosquittopp;
}

struct ClientTag
{
    std::string tagName;
    std::string topicName;
    MqttVarType mqttVarType;
    bool onOff;
    std::string systemName;
    ClientActions clientActions;
};

struct Business{
        std::string name;
        int32_t size;
        float trpersec;
      };

struct MqttClient
{
    std::string clientName;
    std::string clientID;
    Protocol protocol;
    std::string hostAddress;
    int32_t hostPort;
    std::string userName;
    std::string userPassword;
    int32_t reConnect;
    int32_t timeOut;
    std::string willTopic;
    Qos willQos;
    std::string willPayLoad;
    bool sendTimestamp;
    bool keepAlive;
    int32_t keepAliveTime;
    bool mqtt31Compatilble;
    bool willRetain;
    bool cleanSession;
    std::vector<ClientTag> clientTag;
    Qos qos;
    int32_t publishInterval;
    bool retain;
    Business business;
};

class MqttClientsConfigService final : public MqttClientsConfig::Service
{
private:
    // CONNECTION::ConnectionManager *connMan;
    std::vector<MqttClient> mqttClients;
    void ExtractMqttClientConfig();
    virtual ::grpc::Status SendMqttClientsConfig(::grpc::ServerContext *context, const ::MqttClients *request, ::ConfigResponse *response) override;
    CONNECTION::ConnectionManager *connMan;

public:
    MqttClientsConfigService(CONNECTION::ConnectionManager *ConnMan);
};

class MqttBrokerConfigService final : public MqttBrokerConfig::Service
{
    virtual ::grpc::Status SendMqttBrokerConfig(::grpc::ServerContext *context, const ::MqttBorker *request, ::ConfigResponse *response) override;
};
