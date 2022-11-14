//
// Created by aziz on 22.08.21.
//

#ifndef EVENT_MANAGER_MQTTPUBLISHER_H
#define EVENT_MANAGER_MQTTPUBLISHER_H
#include "Mqtt.h"

namespace MqTT
{
class MqttPublisher: public Mqtt
{

protected:
    void Init();
    void Act();
    std::vector<std::string> vstrPayloads{};
    int QoS{0};
public:

    MqttPublisher(std::string addr, std::string id);
    MqttPublisher(stClient);
    ~MqttPublisher();
    void SetTopic(std::string s)
    {
        strTopicName = s;
    };
    void SetQos(int qos)
    {
        QoS = qos;
    }
    void SetPayload(std::vector<std::string> &p);

};
}


#endif //EVENT_MANAGER_MQTTPUBLISHER_H
