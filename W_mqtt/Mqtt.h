#ifndef MQTT_H
#define MQTT_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <functional>

#include <mqtt/async_client.h>
#include <mqtt/topic.h>
#include <shared_mutex>

#define SLEEP_MQTT 5000

struct stClient {
    std::string strAddress{"tcp://localhost:1883"};
    std::string strId{""};
};

namespace MqTT
{


using ClientType = mqtt::async_client;
using ErrHandler = std::function<void(std::string err)>;

class Mqtt
{
protected:

    virtual void Connect(bool publisher =false);
    virtual void Disconnect();
    virtual void Init()=0;
    virtual void Act()=0;  // function call topic and publish and subscrip
    ClientType Client;
    std::vector<ClientType> connectors;
    std::string strTopicName{"time"};
    std::list<mqtt::topic> TopicS;
    std::string strID ;
    mqtt::connect_options ConOpts;
    ErrHandler ErrCallBack;
    
public:
    void setErrCallBack(const ErrHandler &errCallBack);
    Mqtt() = delete;
    Mqtt(std::string address, std::string id);
    Mqtt(stClient c);
    bool findclient(std::string address);
    virtual ~Mqtt();
    virtual void Run(); // main in side function
    virtual void connection_lost(const std::string& cause) {}
    void SetHandler(mqtt::async_client::message_handler cb );
    void SetHandler(mqtt::async_client::connection_handler cb, bool connect_b );
    void SetHandler(mqtt::async_client::disconnected_handler cb );
    void SetHandler(mqtt::async_client::update_connection_handler cb );

    void SetConnectOptions(mqtt::connect_options opts)
    {
        ConOpts = opts;
    };
    void SetCallback(mqtt::callback cb)
    {
        Client.set_callback(cb);
    };
};
}

#endif