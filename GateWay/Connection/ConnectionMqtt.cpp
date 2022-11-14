//
// Created by aziz on 15.09.21.
//

#include "ConnectionMqtt.h"
MqttProtocol StrToProtocol(std::string str)
{
    if (str.empty()) {
        return MqttProtocol::ERR;
    }
    if (strcmp("WS", str.c_str())) {
        return MqttProtocol::WS;
    }
    if (strcmp("WSS", str.c_str())) {
        return MqttProtocol::WSS;
    }
    if (strcmp("TCP", str.c_str())) {
        return MqttProtocol::MQTT_TCP;
    }
    if (strcmp("TLS", str.c_str())) {
        return MqttProtocol::MQTT_TLS;
    }
    return MqttProtocol::ERR;

}

std::string Pro2Str(MqttProtocol p)
{
    std::string str;
    switch (p) {
    case MqttProtocol::MQTT_TLS:
        str = "MQTT::TLS";
        break;
    case MqttProtocol::MQTT_TCP:
        str = "MQTT::TCP";
        break;
    case MqttProtocol::WSS:
        str="WSS";
        break;
    case MqttProtocol::WS:
        str="WS";
        break;
    case MqttProtocol::ERR:
        str="ERR";
        break;
    default:
        str="ERR";
        break;
    }
    return str;
}

void ConnectionMqtt::print()
{
    Connection::print();
    std::cout << "ID : " << ID.Value << '\n'
              << "Protocol : " << Pro2Str(Protocol.Value) << '\n'
              << "Username : " << Username.Value << '\n'
              << "Password : " << Password.Value <<'\n'
              << "Reconnect Period : " << ReconnectPeriod.Value << '\n'
              << "Connect Timeout : " << ConnectTimeout.Value << '\n'
              << "Keep Alive : " << KeepAlive.Value << '\n'
              << "Will Topic : " << WillTopic.Value << '\n'
              << "Will QoS : " << WillQoS.Value << '\n'
              << "WillRetain : " << WillRetain.Value << '\n'
              << "Clean Session : " << CleanSession.Value << '\n'
              << "ReschedulePings : " << ReschedulePings.Value << '\n'
              //<< MQTTv3_1_compliant<< << '\n'
              << "Will Payload : " << WillPayload.Value << '\n'
              << "QoS Zero : "<< QoSZero.Value << '\n'
              << "Execution Retry : "<< ExecutionRetry.Value << '\n'
              << "Retry Interval : "<< RetryInterval.Value << '\n'
              << "Retries Interval Unit : " << RetriesIntervalUnit.Value << '\n';

    for (auto Tag : NodeS) {
        auto mqtt = reinterpret_cast<xmlMqtt*>(Tag);
        mqtt->print();
    }
}



void ConnectionMqtt::SpecialInfo(pugi::xml_node &Special)
{

    ID.Value = Special.child("ID").child_value();
    Protocol.Value = StrToProtocol(Special.child("Protocol").child_value());
    Username.Value = Special.child("Username").child_value();
    Password.Value = Special.child("Password").child_value();
    std::string str = Special.child("ReconnectPeriod").child_value();
    ReconnectPeriod.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));
    str = Special.child("ConnectTimeout").child_value();
    ConnectTimeout.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));
    str = Special.child("KeepAlive").child_value();
    KeepAlive.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));
    WillTopic.Value = Special.child("WillTopic").child_value();
    WillQoS.Value = Special.child("WillRetain").child_value();
    WillRetain.Value = Special.child("Topic").child_value();
    //AppendTimestamp.Value = Special.child("Topic").child_value();
    str = Special.child("CleanSession").child_value();
    CleanSession.Value = (uint8_t)(str.empty() ? 0 : std::stoul(str));
    str = Special.child("ReschedulePings").child_value();
    ReschedulePings.Value = (uint8_t)(str.empty() ? 0 : std::stoul(str));
    //str = Special.child("MQTTv3_1_compliant").child_value();
    //MQTTv3_1_compliant.Value = str.empty() ? 0 : std::stoul(str);
    str = Special.child("WillPayload").child_value();
    WillPayload.Value = (uint8_t)(str.empty() ? 0 : std::stoul(str));
    str = Special.child("QoSZero").child_value();
    QoSZero.Value = (uint8_t)(str.empty() ? 0 : std::stoul(str));
    str = Special.child("ExecutionRetry").child_value();
    ExecutionRetry.Value = (uint8_t)(str.empty() ? 0 : std::stoul(str));
    str = Special.child("RetryInterval").child_value();
    RetryInterval.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));
    str = Special.child("RetriesIntervalUnit").child_value();
    RetriesIntervalUnit.Value = (uint16_t)(str.empty() ? 0 : std::stoul(str));

}

void ConnectionMqtt::SpecialInfoGRPC()
{


}


ConnectionMqtt::ConnectionMqtt()
{
    IProtocol = ProtocolIIOT::MQTT;
    Address.Value ="tcp://";
}

void ConnectionMqtt::NodeSInfo(pugi::xml_node &Node)
{
    for (pugi::xml_node Tag: Node.children("Tag")) {
        xmlMqtt * n{new xmlMqtt{}};
        n->SetData(Tag);
        NodeS.push_back(n);
    }
}

strTag ConnectionMqtt::getID() {
    return ID;
}

void xmlMqtt::SpecialInfo(pugi::xml_node &Special)
{
    Topic.Value = Special.child("Topic").child_value();
    Prefix.Value = Special.child("Prefix").child_value();
    clientAction = static_cast<ClientActions>( std::stoul(Special.child("Action").child_value()));
    
}

void xmlMqtt::SpecialInfoGRPC()
{
}


void xmlMqtt::print()
{
    xmlNode::print();
    std::cout << "Topic : " << Topic.Value << '\n'
              << "Prefix : " << Prefix.Value << '\n';
}
