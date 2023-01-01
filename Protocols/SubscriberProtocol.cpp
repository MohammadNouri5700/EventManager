//
// Created by aziz on 03.08.21.
//

#include "SubscriberProtocol.h"


ProtocolS::Mqtt::SubscriberProtocol::SubscriberProtocol():MqttSubscriber(stClient{}) {}

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
            {
                std::string s = msg->get_payload_str();
                if (m->clientAction ==SUB){
                    int posstart = s.find(m->Name.Value);
                    std::string sub = s.substr(posstart);
                    int pos_sec_start = sub.find(":");
                    sub =  sub.substr(pos_sec_start+1);
                    int posend = sub.find(",");
                    sub =  sub.substr(0,posend);
                    ReplaceAll(sub,"\"\\\\\\\"","");
                    ReplaceAll(sub,"\\\\\\\"\"","");
                    ReplaceAll(sub," ","");
                    std::cout<<sub<<std::endl;
                    if (sub.find("true") != -1){
                        sub="true";
                    }else if(sub.find("false") !=-1 ){
                        sub="false";
                    }
                    m->setValue((void *)sub.c_str(), strlen(sub.c_str()));
                }else{
                    std::cout<<"we cannot find Value"<<std::endl;
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
    Client.connect();
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
    MqTT::MqttSubscriber::Stop();
}



