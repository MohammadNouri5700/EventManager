//
// Created by aziz on 18.09.21.
//

#include "NewPublisher.h"
#include "../GateWay/SignalS.h"

void MqTT::NewPublisher::Run()
{
    try {
        //const std::lock_guard<std::mutex> lock(g_i_mutex);

        Act();
        //Disconnect();

    } catch (const mqtt::exception& exc) {
        std::cerr << "\n" << exc << std::endl;
        ErrCallBack(exc.to_string()+"my pub");
    }
}

MqTT::NewPublisher::NewPublisher(const std::string &addr, const std::string &id) : MqttPublisher(addr, id)
{
    std::cout << "**Publisher ID :" << id << std::endl;
    Connect(true);
}
