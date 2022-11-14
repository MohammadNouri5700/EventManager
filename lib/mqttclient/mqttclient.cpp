#include "mqttclient.h"
#include <iostream>

mosqpp::MqttClient::MqttClient(const char *id, bool clean_session)
    : mosquittopp(id, clean_session), stopped(true), running(false)
{

}

mosqpp::MqttClient::~MqttClient()
{
    stop();
    std::cout << "MqttClient destructor" << std::endl;
}

int mosqpp::MqttClient::AddTag(ClientTag tag)
{
    tags[tag.topicName] = tag;
    return 0;
}

mosqpp::ClientTags mosqpp::MqttClient::GetTags()
{
    return tags;
}

void mosqpp::MqttClient::on_message(const struct mosquitto_message *message)
{
    std::cout << message->qos << " " << message->mid << " " << message->topic <<
              " " << std::string((char*)message->payload, message->payloadlen) << std::endl;
    tags[message->topic].message = std::string((char*)message->payload, message->payloadlen);
}

void mosqpp::MqttClient::start()
{
    loop_start();
    stopped = false;
    thread = std::thread(&mosqpp::MqttClient::background_thread_publish, this);
}

void mosqpp::MqttClient::stop()
{
    {
        std::lock_guard<std::mutex> l(mx);
        stopped = true;
    }
    cv.notify_one();
    thread.join();
    disconnect();
    loop_stop();
}

void mosqpp::MqttClient::background_thread_publish()
{
    while (!stopped) {
        for (auto& tag_pair : tags) {
            auto& tag = tag_pair.second;
            if (tag.clientActions == ClientActions::PUB || tag.clientActions == ClientActions::PUB_SUB) {
                if (tag.onOff) {
                    publish(NULL, tag.topicName.c_str(), tag.message.size(), tag.message.c_str(), qos, retain);
                }
            }
        }
        std::unique_lock<std::mutex> l(mx);
        cv.wait_for(l, std::chrono::milliseconds(publishInterval));
    }
}
