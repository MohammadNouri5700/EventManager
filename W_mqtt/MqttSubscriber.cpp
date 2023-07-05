//
// Created by aziz on 22.08.21.
//
#include <nlohmann/json.hpp>
#include "MqttSubscriber.h"
#include <memory>
#include <shared_mutex>
#include<unistd.h>

extern bool IsinSending;
extern std::shared_mutex mutex_;

MqTT::MqttSubscriber::MqttSubscriber(stClient c) : Mqtt{c.strAddress, c.strId} {


}

MqTT::MqttSubscriber::~MqttSubscriber() {
    std::cout << "MqttSubscriber called " << std::endl;
}


void MqTT::MqttSubscriber::Act() {


    sleep(3);
    while (IsinSending) {}
    for (auto topics: TopicS) {

        while (true) {
            if (!IsinSending) {//Preventing of concurrently in publish and sub
                if (Client.is_connected()) {
                    mqtt::const_message_ptr messagePointer;
                    Client.try_consume_message(&messagePointer);
                } else {
                    Client.connect()->wait();
                    Client.subscribe(topics.get_name(), 0);
                    Client.start_consuming();
                }
            } else {
//                std::cout << "MqttSubscriber stopeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeed " << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
//            sleep(1);
        }
        break;
    }



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


