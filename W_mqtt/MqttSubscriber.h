//
// Created by aziz on 22.08.21.
//

#ifndef EVENT_MANAGER_MQTTSUBSCRIBER_H
#define EVENT_MANAGER_MQTTSUBSCRIBER_H
#include "Mqtt.h"
#include <atomic>
namespace MqTT
{
class MqttSubscriber:public Mqtt
{
protected:
    void Init();
    void Act();
    int QoS{1};
    std::atomic_bool bStopThread{false};
public:
    MqttSubscriber():MqttSubscriber(stClient{}) {};
    MqttSubscriber(stClient);
    ~MqttSubscriber();

    void SetTopic(std::string t, int qos);

    void Stop();
};
}


#endif //EVENT_MANAGER_MQTTSUBSCRIBER_H
