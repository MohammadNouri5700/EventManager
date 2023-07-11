//
// Created by aziz on 03.08.21.
//

#include "SubscriberProtocol.h"
#include <algorithm>

ProtocolS::Mqtt::SubscriberProtocol::SubscriberProtocol():MqttSubscriber(stClient{}) {

    // mqtt::topic topic {Client, strTopicName, QoS };

    std::cout << "Sub..123########################" <<std::endl;
}

ProtocolS::Mqtt::SubscriberProtocol::SubscriberProtocol(const stClient &s) : MqttSubscriber(s)
{
    std::cout << "Sub..########################" <<std::endl;

    auto cb =[this](mqtt::const_message_ptr msg) {
        auto f =[msg](MqttTag *t)->bool{
            return (strcmp(t->Topic.Value.c_str(), msg->get_topic().c_str())==0);
        };
        for (auto i:Observer) {
            auto m = reinterpret_cast<MqttTag*>(i);
            bool b = f(m);
            if (b) {
                std::string s = msg->get_payload_str();
                m->setValue((void*)s.c_str(),strlen(s.c_str()));
            }
        }

    };
    Client.set_message_callback(cb);
}

ProtocolS::Mqtt::SubscriberProtocol::~SubscriberProtocol()
{

}
void ProtocolS::Mqtt::SubscriberProtocol::Listen()
{
    Run();
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

ProtocolS::Mqtt::SubscriberProtocol::SubscriberProtocol(ConnectionMqtt *Conn) : MqttSubscriber(stClient{Conn->Address.Value, Conn->ID.Value})
{
    auto cb = [this](mqtt::const_message_ptr msg)
    {
        auto f = [msg](MqttTag *t) -> bool
        {
            return (strcmp(t->Topic.Value.c_str(), msg->get_topic().c_str()) == 0);
        };
        for (auto i : Observer)
        {
            auto m = reinterpret_cast<MqttTag *>(i);
            bool b = f(m);
            if (b)
            { // TODO HERE IS THE BASIC EDGE
            // WE HAVE TO DO THIS IN CENTERAL
                std::string s = msg->get_payload_str();

            std::cout << "got message == "<< s <<std::endl;
            try{

            
                    json content = json::parse(s).at("content");
                    std::string contentstr = content.dump();
                
                    contentstr.erase(std::remove(contentstr.begin(), contentstr.end(), '\\'), contentstr.end());
                    contentstr.erase(contentstr.begin(), contentstr.begin()+1);
                    contentstr.erase(contentstr.end()-1, contentstr.end());

                    content = json::parse(contentstr);
                    json deviceTwinDocument = content.at("deviceTwinDocument");
                    json attributes = deviceTwinDocument.at("attributes");
                    json desired = attributes.at("desired");
                    desired.erase("$metadata");
                    desired.erase("$version");
                    if (desired.find(m->Notes.Value) != desired.end()) {

                    
                        std::cout << m->Name.Value << "  ==  "  << desired.at(m->Notes.Value) << std::endl;

                        std::string sub = desired.at(m->Notes.Value).dump();

                        m->setValue((void *)sub.c_str(), strlen(sub.c_str()));



                    }
                }catch (const std::bad_function_call& e) {
                    std::string sub = "Read sub value Error";
                    m->setValue((void *)sub.c_str(), strlen(sub.c_str()));
                }



            }
        }
    };
    Client.set_message_callback(cb);
}



void ProtocolS::Mqtt::SubscriberProtocol::Create(Connection *Conn)
{
    (void)Conn; // TODO
}

void ProtocolS::Mqtt::SubscriberProtocol::Open(Connection *Conn)
{
    ErrCallBack("Client is trying to create another session");
    // Client.connect();
}

void ProtocolS::Mqtt::SubscriberProtocol::Close()
{
    Client.disconnect();
}

void ProtocolS::Mqtt::SubscriberProtocol::KeepAlive()
{

}

bool ProtocolS::Mqtt::SubscriberProtocol::isOK()
{
    return Client.is_connected();
}

void ProtocolS::Mqtt::SubscriberProtocol::Reconnect()
{

}

void ProtocolS::Mqtt::SubscriberProtocol::hasError()
{

}

void ProtocolS::Mqtt::SubscriberProtocol::DataReceived()
{
}

void ProtocolS::Mqtt::SubscriberProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}

void ProtocolS::Mqtt::SubscriberProtocol::Write(Data* data,Tag* tag)
{
    Protocol::Write(data,tag);
}

void ProtocolS::Mqtt::SubscriberProtocol::Stop()
{
    bStopThread = true;
    // MqTT::MqttSubscriber::Stop();
}



