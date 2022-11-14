//
// Created by aziz on 22.08.21.
//

#include "MqttSubscriber.h"
#include <memory>

MqTT::MqttSubscriber::MqttSubscriber(stClient c): Mqtt{c.strAddress, c.strId}
{

}

MqTT::MqttSubscriber::~MqttSubscriber()
{

}


void MqTT::MqttSubscriber::Act()
{

    //mqtt::topic topic {Client, strTopicName, QoS };

    std::cout << "\nOk.\nstarting subscriber"<<  std::flush;

    for (auto topic: TopicS) {
        try {
            std::cout << "\nOk.\nsubscribe"<< topic.get_name()<< std::flush;
            topic.subscribe()->wait();
            
            std::cout << "\nOk.. "<<std::endl;
        } catch (const mqtt::exception& exc) {
            std::cerr << "\nERROR: Unable to Connect. "<< exc.get_message()<<exc.get_reason_code()
                      << exc.what() << "---"<<std::endl;
            ErrCallBack(exc.to_string()+ "----");
        }
    }
    while (!bStopThread) {
    }
}

void MqTT::MqttSubscriber::Init()
{
}

void MqTT::MqttSubscriber::SetTopic(std::string t, int qos =1)
{
    mqtt::topic topic {Client, t, qos };
    TopicS.push_back(topic);
}

void MqTT::MqttSubscriber::Stop()
{
    std::cerr << "void MqTT::MqttSubscriber::Stop()" << std::endl;
    bStopThread = true;
}


