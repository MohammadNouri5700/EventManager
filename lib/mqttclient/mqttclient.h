#pragma once
#include "mosquittopp.h"
#include <memory>
#include <map>
#include <string>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace mosqpp
{
enum class MqttVarType {
    PLAIN = 0,
    JSON = 1,
    CSV = 2,
};
enum ClientActions{
    PUB = 0,
    SUB = 1,
    PUB_SUB = 2,
};
enum Qos{
    ALMOST_ONCE = 0,
    ATLEAST_ONCE = 1,
    EXACTLY_ONCE = 2,
};
struct ClientTag {
    std::string tagName;
    std::string topicName;
    MqttVarType mqttVarType;
    bool onOff;
    std::string systemName;
    ClientActions clientActions;
    std::string message;
};
using ClientTags=std::map<std::string, ClientTag>;
class  MqttClient : public mosquittopp
{
public:
    MqttClient(const char *id=NULL, bool clean_session=true);
    ~MqttClient();
    int AddTag(ClientTag tag);
    ClientTags GetTags();
    void on_message(const struct mosquitto_message *message);
    Qos getQos() const { return qos; }
    void setQos(const Qos &qos_) { qos = qos_; }
    int getPublishInterval() const { return publishInterval; }
    void setPublishInterval(int publishInterval_) { publishInterval = publishInterval_; }
    void start();
    void stop();
    bool getRetain() const { return retain; }
    void setRetain(bool retain_) { retain = retain_; }
private:
    ClientTags tags;
    void background_thread_publish();
    Qos qos;
    int publishInterval;
    std::atomic_bool stopped;
    std::atomic_bool running;
    bool retain;
    std::condition_variable cv;
    std::mutex mx;
    std::thread thread;
};
}