//
// Created by aziz on 03.08.21.
//

#include "PublisherProtocol.h"


ProtocolS::Mqtt::PublisherProtocol::PublisherProtocol():MqttPublisher(stClient{}) {}

ProtocolS::Mqtt::PublisherProtocol::PublisherProtocol(const stClient &s) : MqttPublisher(s)
{
    auto cb =[this](mqtt::const_message_ptr msg) {
        auto f =[msg](MqttTag *t)->bool{
            return (strcmp(t->Topic.Value.c_str(), msg->get_topic().c_str())==0);
        };
        for (auto i:Observer) {
            auto m = reinterpret_cast<MqttTag*>(i);
            bool b = f(m);
            if (b) {
                std::string s = msg->get_payload_str();
                m->setValue(s.data(),s.length());
            }
        }

    };
    Client.set_message_callback(cb);
}

ProtocolS::Mqtt::PublisherProtocol::~PublisherProtocol()
{

}
void ProtocolS::Mqtt::PublisherProtocol::Listen()
{
    Run();
}

ProtocolS::Mqtt::PublisherProtocol::PublisherProtocol(ConnectionMqtt *Conn):MqttPublisher(stClient{Conn->Address.Value, Conn->ID.Value})
{
    auto cb =[this](mqtt::const_message_ptr msg) {
        auto f =[msg](MqttTag *t)->bool{
            return (strcmp(t->Topic.Value.c_str(), msg->get_topic().c_str())==0);
        };
        for (auto i:Observer) {
            auto m = reinterpret_cast<MqttTag*>(i);
            bool b = f(m);
            if (b) {
                std::string s = msg->get_payload_str();
                m->setValue(s.data(),s.length());
            }
        }

    };
    Client.set_message_callback(cb);
}

void ProtocolS::Mqtt::PublisherProtocol::Create(Connection *Conn)
{
    (void)Conn; // TODO
}

void ProtocolS::Mqtt::PublisherProtocol::Open(Connection *Conn)
{
    Client.connect();
}

void ProtocolS::Mqtt::PublisherProtocol::Close()
{
    Client.disconnect();
}

void ProtocolS::Mqtt::PublisherProtocol::KeepAlive()
{

}

bool ProtocolS::Mqtt::PublisherProtocol::isOK()
{
    return Client.is_connected();
}

void ProtocolS::Mqtt::PublisherProtocol::Reconnect()
{

}

void ProtocolS::Mqtt::PublisherProtocol::hasError()
{

}

void ProtocolS::Mqtt::PublisherProtocol::DataReceived()
{
}

void ProtocolS::Mqtt::PublisherProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}

void ProtocolS::Mqtt::PublisherProtocol::Write(Data* data,Tag* tag)
{
    Protocol::Write(data,tag);
}


