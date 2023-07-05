//
// Created by aziz on 15.09.21.
//

#ifndef XML_CONNECTIONMQTT_H
#define XML_CONNECTIONMQTT_H

#include <mqtt/async_client.h>
#include "Connection.h"
#include "../../GrpcServer/mqttservice.h"


using ClientType = mqtt::async_client;
enum class MqttProtocol {ERR, WS, WSS, MQTT_TCP, MQTT_TLS};

using proTag = XmlTag<MqttProtocol>;
using bTage = XmlTag<bool>;


struct xmlMqtt : public  xmlNode {
    strTag Topic{};
    strTag Prefix{};
    ClientActions clientAction{};
    
    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    void print() override;
};


struct ConnectionMqtt : public Connection {


    strTag ID{};
    proTag Protocol{};
    strTag Username{};
    strTag Password{};
    u16Tag ReconnectPeriod{};
    u16Tag ConnectTimeout{};
    u16Tag KeepAlive{};
    bTag WillTopic{};
    strTag WillQoS{};
    strTag WillRetain{};
    //AppendTimestamp;
    u8Tag CleanSession{};
    u8Tag ReschedulePings{};
    //u8Tag MQTTv3_1_compliant;
    u8Tag WillPayload{};
    u8Tag QoSZero{};
    u8Tag ExecutionRetry{};
    u16Tag RetryInterval{};
    u16Tag RetriesIntervalUnit{};
    
    
    void print() override;

    void SpecialInfo(pugi::xml_node &Special) override;
    void SpecialInfoGRPC() override;
    void NodeSInfo(pugi::xml_node &Node) override;

    strTag getID();

    ConnectionMqtt();
};


#endif //XML_CONNECTIONMQTT_H
