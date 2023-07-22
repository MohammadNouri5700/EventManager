//
// Created by aziz on 18.09.21.
//
#include <chrono>
#include "NewPublisher.h"
#include "../GateWay/SignalS.h"
#include "MqttSubscriber.h"


using namespace std::chrono;


void MqTT::NewPublisher::Run()
{
    try {
        //const std::lock_guard<std::mutex> lock(g_i_mutex);

       Act();



//            mqtt::const_message_ptr messagePointer;
//            if (Client.is_connected()){
//                    Client.subscribe(TopicS.rbegin()->get_name(), 0);
//                    Client.start_consuming();
//                    if(Client.try_consume_message_for(&messagePointer,std::chrono::microseconds(5000))){
//                        std::string messageString = messagePointer -> get_payload_str();
//                        std::cout << messageString << std::endl;
//                    }
//            }





        //Disconnect();

    } catch (const mqtt::exception& exc) {
        std::cerr << "\n" << exc << std::endl;
        ErrCallBack(exc.to_string()+"my pub");
    }
}

MqTT::NewPublisher::NewPublisher(const std::string &addr, const std::string &id) : MqttPublisher(addr, id)
{
    std::cout << "**Publisher ID :" << id << std::endl;
//    Connect(true);
}
