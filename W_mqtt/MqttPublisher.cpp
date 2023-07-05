#include "MqttPublisher.h"
#include <iostream>
#include "../GateWay/SignalS.h"
#include <mutex>          // std::mutex
#include <chrono>

extern bool IsinSending;
extern int64_t recent;


using namespace std::chrono;
extern std::shared_mutex mutex_;

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

    int64_t timestamp = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

    // if (recent==0){
    //     recent=timestamp;
    // }else if (recent==timestamp){
    //     return;
    // }


    mqtt::topic Topic(Client, strTopicName, QoS);
    mqtt::token_ptr tok;
    std::cout << "starting publisher..." << timestamp << std::endl;

    Topic.set_qos(0);

    Topic.set_retained(false);
  //  std::ofstream outFile;
    //outFile.open("log_mqtt.txt", std::ios_base::app);
    auto now =  std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());


    for (auto payload : vstrPayloads)
    {

        try
        {
            std::string temp;
            if (!Client.is_connected())
            {
                 Client.connect()->wait();
            }

            std::cout << "Publishing Topic: " << strTopicName << std::endl;
            //  tok = Topic.publish(payload.c_str());
            //tok = Topic.publish(temp.c_str());
            Topic.publish(payload.c_str())->wait();
            std::cout << "Publishing: " << temp.c_str() << std::endl;
            std::cout << "void MqTT::MqttPublisher::Act() "
                      << "publish " << payload << std::endl;

         //   outFile << payload.c_str() << "Time : " << std::ctime(&now);


//            tok->wait();

        }
        catch (std::exception &e)
        {
            std::cout << "void MqTT::MqttPublisher::Act()" << e.what() << std::endl;
        }
    }
    vstrPayloads.clear();

    std::cout << "OK" << std::endl;
    Client.disconnect();
    IsinSending=false;



}

void MqTT::MqttPublisher::SetPayload(std::vector<std::string> &p)
{
    for (auto s : p)
    {
        vstrPayloads.push_back(s);
    }
}