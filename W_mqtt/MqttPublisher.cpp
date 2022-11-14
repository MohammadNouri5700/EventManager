//
// Created by aziz on 22.08.21.
//

#include "MqttPublisher.h"
#include <iostream>
#include "../GateWay/SignalS.h"

MqTT::MqttPublisher::MqttPublisher(std::string adrr, std::string id) : Mqtt{adrr, id}
{
    std::cout << "**Publisher :" << id << std::endl;

    vstrPayloads.clear();
}

MqTT::MqttPublisher::MqttPublisher(stClient client) : Mqtt{client.strAddress, client.strId}
{
    std::cout << "Publisher :" << client.strId << std::endl;
}

MqTT::MqttPublisher::~MqttPublisher()
{
}

void MqTT::MqttPublisher::MqttPublisher::Init()
{
}

void MqTT::MqttPublisher::Act()
{
    mqtt::topic Topic(Client, strTopicName, QoS);
    mqtt::token_ptr tok;
    std::cout << "starting publisher..." << std::endl;

    Topic.set_qos(0);

    Topic.set_retained(true);
    std::ofstream outFile;
    outFile.open("log_mqtt.txt", std::ios_base::app);
    auto now =  std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    for (auto payload : vstrPayloads)
    {
        try
        {
            std::string temp;
            if (!Client.is_connected())
            {
                std::cout << "Client Is not Connected ,Try to connect... " << std::endl;
                Client.connect()->wait();
            }

            std::cout << "Publishing Topic: " << strTopicName << std::endl;
             tok = Topic.publish(payload.c_str());
            //tok = Topic.publish(temp.c_str());
            Topic.publish(temp.c_str())->try_wait();
            std::cout << "Publishing: " << temp.c_str() << std::endl;
            std::cout << "void MqTT::MqttPublisher::Act() "
                      << "publish " << payload << std::endl;

            outFile << payload.c_str() << "Time : " << std::ctime(&now);


            tok->wait();
        }
        catch (std::exception &e)
        {
            std::cout << "void MqTT::MqttPublisher::Act()" << e.what() << std::endl;
        }
    }
    vstrPayloads.clear();
    std::cout << "OK" << std::endl;
}

void MqTT::MqttPublisher::SetPayload(std::vector<std::string> &p)
{
    for (auto s : p)
    {
        vstrPayloads.push_back(s);
    }
}