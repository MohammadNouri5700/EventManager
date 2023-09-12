//
// Created by aziz on 22.08.21.
//
#include <nlohmann/json.hpp>
#include "MqttSubscriber.h"
#include "../GateWay/ConvertS/OutputNode.h"
#include <memory>
#include <shared_mutex>
#include<unistd.h>


std::mutex mtx;
extern bool IsinSending;
extern bool waitPub;
extern std::vector<OutputNode *> OutnodeS;

MqTT::MqttSubscriber::MqttSubscriber(stClient c) : Mqtt{c.strAddress, c.strId} {


}

MqTT::MqttSubscriber::~MqttSubscriber() {
    std::cout << "MqttSubscriber called " << std::endl;
}


void MqTT::MqttSubscriber::Act() {


    mqtt::const_message_ptr messagePointer;

//    sleep(5);
//    mqtt::topic Topic(Client, strTopicName, QoS);


//    while (IsinSending) {}

    LOOP:
    do {
        try {
            mtx.lock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::atomic_bool res = false;
            for (auto n: OutnodeS) {
                if (strcmp(TopicS.begin()->get_client().get_client_id().c_str(), n->OutputNodeID.Value.c_str()) == 0) {
                    if (n->isbusy) {
                        res = true;
                        break;
                    }
                }
            }


            if (!res) {
                if (Client.is_connected()) {
                    Client.try_consume_message(&messagePointer);
                } else {
                    Client.connect()->wait();
                    std::cout << "try_consume_message == " << TopicS.begin()->get_client().get_client_id();
                    Client.subscribe(TopicS.begin()->get_name(), 0);
                    Client.start_consuming();
                }
            }
            mtx.unlock();
        } catch (const mqtt::exception &exc) {
            std::cout << "\n!@! MQTT EXCEPTION  in sub   " << TopicS.begin()->get_name() << std::endl;
            mtx.unlock();
        }
    } while (true);
    std::cout << "try_consume_message == ERROR ";
    goto LOOP;

    std::cout << "finish =============================================================";
//    std::exit(1);
// while (!bStopThread && Client.is_connected()) {
//     mqtt::const_message_ptr messagePointer;
//     Client.try_consume_message(&messagePointer);
// }
// std::cout << "Client Is not Connected ,Try to connect... " << std::endl;

// //    0LF5KW2MRLS457OYH2JKCNS
// std::cout << "\nOk.\nstarting subscriber"<<  std::flush;

// while(!Client.is_connected()){

// }
// for (auto topic: TopicS) {
//     try {
//         if(!isCunsume){

//         if (!Client.is_connected())
//         {
//             throw std::invalid_argument( "received negative value" );
//             // std::cout << "Client Is not Connected ,Try to connect... " << std::endl;
//             // Client.connect()->wait();
//         }

//             isCunsume = true;
//             std::cout << "\nOk.\nsubscribe    "<< topic.get_name()<< std::flush;
// //            topic.subscribe()->wait();
//             Client.subscribe(topic.get_name(),0);//Almost Once
//             Client.start_consuming();
//             std::cout << "\nOk.. "<<std::endl;
//          }
//     } catch (const mqtt::exception& exc) {
//         std::cerr << "\nERROR: Unable to Connect. "<< exc.get_message()<<exc.get_reason_code()
//                   << exc.what() << "---"<<std::endl;
//         ErrCallBack(exc.to_string()+ "----");
//     }
// }
// while (!bStopThread) {
//    // Construct a message pointer to hold an incoming message.
//     mqtt::const_message_ptr messagePointer;

//     // Try to consume a message, passing messagePointer by reference.
//     // If a message is consumed, the function will return `true`,
//     // allowing control to enter the if-statement body.
//     if (Client.try_consume_message(&messagePointer))
//     {
//         // Construct a string from the message payload.
//         // std::string messageString = messagePointer -> get_payload_str();
//         // Print payload string to console (debugging).
//         // std::cout << messageString << std::endl;

//         // Perform processing on the string.
//         // This is where message processing can be passed onto different
//         // functions for parsing.
//         // Here, we break the loop and exit the program if a `quit` is received.
//     }

// }
}

void MqTT::MqttSubscriber::Init() {

}

void MqTT::MqttSubscriber::SetTopic(std::string t, int qos = 1) {
    mqtt::topic topic{Client, t, qos};
    TopicS.push_back(topic);
}

void MqTT::MqttSubscriber::Stop() {
    std::cerr << "void MqTT::MqttSubscriber::Stop()" << std::endl;
    bStopThread = true;
}


