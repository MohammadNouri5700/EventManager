//
// Created by aziz on 22.08.21.
//
#include <nlohmann/json.hpp>
#include "MqttSubscriber.h"
#include <memory>

MqTT::MqttSubscriber::MqttSubscriber(stClient c): Mqtt{c.strAddress, c.strId}
{

}

MqTT::MqttSubscriber::~MqttSubscriber()
{

}


void MqTT::MqttSubscriber::Act()
{

//    mqtt::topic topic {Client, strTopicName, QoS };
//    0LF5KW2MRLS457OYH2JKCNS
    std::cout << "\nOk.\nstarting subscriber"<<  std::flush;

    for (auto topic: TopicS) {
        try {
            std::cout << "\nOk.\nsubscribe    "<< topic.get_name()<< std::flush;
//            topic.subscribe()->wait();
            Client.subscribe(topic.get_name(),0);//Almost Once
            Client.start_consuming();
            std::cout << "\nOk.. "<<std::endl;
        } catch (const mqtt::exception& exc) {
            std::cerr << "\nERROR: Unable to Connect. "<< exc.get_message()<<exc.get_reason_code()
                      << exc.what() << "---"<<std::endl;
            ErrCallBack(exc.to_string()+ "----");
        }
    }
    while (!bStopThread) {
        mqtt::const_message_ptr messagePointer;

        // Try to consume a message, passing messagePointer by reference.
        // If a message is consumed, the function will return `true`,
        // allowing control to enter the if-statement body.
        if (Client.try_consume_message(&messagePointer))
        {
            //{"id":885896656,"senderId":11337647,"type":3,"content":"{\"deviceTwinDocument\":{\"attributes\":{\"desired\":{},\"reported\":{\"$version\":239,\"Pump102_Run\":\"false\",\"ST_FEED201\":0.0,\"Element101_ON\":\"false\",\"GPS\":\"{MessageID : $GPRMC,UTCTime : 074719.00,Status : A,Latitude : 3545.55404,NSIndicator : N,Longitude : 05124.02713,EWindicator : ,SpeedOverGround : 0.043,CourseOverGround : ,Date : 171222,MagneticVariation : ,Mode : A,Checksum : 7C}\",\"FEED201_Run\":\"false\",\"SV102_Open\":\"false\",\"FAN101_ON\":\"false\",\"Pump101_Run\":\"false\",\"Rope201\":\"true\",\"PT101\":0.0,\"Rope202\":\"true\",\"Start101\":\"false\",\"Start201\":\"false\",\"CONV201_Run\":\"false\",\"ST_Pump101\":0.0,\"ST_Pump102\":0.0,\"CONV203_Run\":\"false\",\"ST_CONV203\":0.0,\"TT101\":23.903357,\"ST_CONV202\":0.0,\"TT102\":23.712383,\"SV101_Open\":\"false\",\"Stop201\":\"false\",\"ST_CONV201\":0.0,\"Stop101\":\"false\",\"LT202\":10.638538,\"CONV202_Run\":\"false\",\"LT201\":3.08893,\"LT102\":2.690972,\"LT101\":19.479168,\"$metadata\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\",\"Pump102_Run\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"ST_FEED201\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"Element101_ON\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"GPS\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"FEED201_Run\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"SV102_Open\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"FAN101_ON\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"Pump101_Run\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"Rope201\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"PT101\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"Rope202\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"Start101\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"Start201\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"CONV201_Run\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"ST_Pump101\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"ST_Pump102\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"CONV203_Run\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"ST_CONV203\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"TT101\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"ST_CONV202\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"TT102\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"SV101_Open\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"Stop201\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"ST_CONV201\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"Stop101\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"LT202\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"CONV202_Run\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"LT201\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"LT102\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"},\"LT101\":{\"$lastUpdate\":\"2022-12-25T06:47:58.366Z\"}}}}},\"$requestId\":null}"}

            // Construct a string from the message payload.
            std::string messageString = messagePointer -> get_payload_str();

            // Print payload string to console (debugging).
        }

    }
}

void MqTT::MqttSubscriber::Init()
{
}

void MqTT::MqttSubscriber::SetTopic(std::string t, int qos =1)
{
    mqtt::topic topic {Client, t, qos };
    TopicS.push_back(topic);
}

void MqTT::MqttSubscriber::Stop()
{
    std::cerr << "void MqTT::MqttSubscriber::Stop()" << std::endl;
    bStopThread = true;
}


