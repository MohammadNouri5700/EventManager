#include "MqttPublisher.h"
#include <iostream>
#include "../GateWay/SignalS.h"
#include <mutex>          // std::mutex
#include <chrono>
#include <mqtt/client.h>

#include "sys/types.h"
#include "sys/sysinfo.h"


#include "stdlib.h"
#include "stdio.h"
#include "string.h"


extern bool IsinSending;
extern bool waitPub;
extern int64_t recent;
extern std::vector<OutputNode *> OutnodeS;

using namespace std::chrono;
std::mutex mu;



int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

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
mqtt::client cliTest("iot-mqtt.pod.ir:1883", "U9MFKW3X53T0VSV4APIH9P3");
void MqTT::MqttPublisher::Act()
{

    for (auto n : OutnodeS)
    {
        if (strcmp(Client.get_client_id().c_str(),n->OutputNodeID.Value.c_str())==0) {
            n->isbusy=true;
        }
    }

    mu.lock();

    int64_t timestamp = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();


//     std::ofstream outFile;
//     outFile.open("log_143.txt", std::ios_base::app);
//
//    struct sysinfo memInfo;
//
//    sysinfo (&memInfo);
//    long long totalVirtualMem = memInfo.totalram;
////Add other values in next statement to avoid int overflow on right hand side...
//    totalVirtualMem += memInfo.totalswap;
//    totalVirtualMem *= memInfo.mem_unit;
//
//    long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
////Add other values in next statement to avoid int overflow on right hand side...
//    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
//    virtualMemUsed *= memInfo.mem_unit;
//
//
//    std::string temp =  std::to_string(getValue()) +"," + std::to_string(timestamp) + "\n";
//    std::cout<<temp;
//    outFile<<temp;




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
//    Topic.set_retained(false);
  //  std::ofstream outFile;
    //outFile.open("log_mqtt.txt", std::ios_base::app);
    auto now =  std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());


    for (auto payload : vstrPayloads)
    {

        try
        {
            waitPub= true;
            std::string temp;
            if (!Client.is_connected())
            {
                std::cout<< "Client.reconnect() PUB  ";
                Client.connect()->wait();
            }

            std::cout << "Publishing Topic: " << strTopicName << std::endl;
            //  tok = Topic.publish(payload.c_str());
            //tok = Topic.publish(temp.c_str());
//            Topic.publish(payload.c_str())->wait();

            Client.publish(strTopicName,payload.c_str(),0,false)->wait_for(20000);
//            Client.disconnect()->wait();
//            Client.disconnect();
            waitPub= false;
//            mqtt::iasync_client dubclient("iot-mqtt.pod.ir:1883", "U9MFKW3X53T0VSV4APIH9P3");
//            mqtt::topic test(static_cast<iasync_client &>(dubclient), "strTopicName", 1);
//            pubmsg->set_qos(0);
//            dubclient.publish(pubmsg);



//            if (!cliTest.is_connected()){
//                cliTest.connect();
//            }
//            auto msg = mqtt::make_message("dvcasy/twin/update/reported", payload.c_str());
//            msg->set_qos(0);
//            cliTest.publish(msg);




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

    for (auto n : OutnodeS)
    {
        if (strcmp(Client.get_client_id().c_str(),n->OutputNodeID.Value.c_str())==0) {
            n->isbusy=false;
        }
    }
    IsinSending=false;
    mu.unlock();
}

void MqTT::MqttPublisher::SetPayload(std::vector<std::string> &p)
{
    for (auto s : p)
    {
        vstrPayloads.push_back(s);
    }
}