#include "Mqtt.h"

MqTT::Mqtt::Mqtt(std::string address, std::string id) : Client(address, id, mqtt::create_options(MQTTVERSION_5)),
                                                        TopicS{}, ConOpts{}, ErrCallBack{} {
    std::cout << "*init ID :" << id << std::endl;
    strID = id;
}

MqTT::Mqtt::~Mqtt() {

}

void MqTT::Mqtt::Run() {
    Init();
    try {
        std::cout << "--Start running mqtt" << std::endl;
        if (TopicS.size()) {
            Connect();
            Act();
            Disconnect();
        }
    }
    catch (const mqtt::exception &exc) {
        std::cerr << "\n!@!" << exc << std::endl;
        ErrCallBack("mqtt Run");
    }
}

void MqTT::Mqtt::Connect(bool publisher) {
    if (TopicS.size() > 0 || publisher) {
        int connect = 0;
        while (connect == 0) {


            try {
                std::cout << "--MQTT" << std::endl;
                std::cout << "\nConnecting... '" << Client.get_server_uri() << " " << Client.get_client_id()
                          << std::endl;
                /// ConOpts.set_clean_session(true);
                /// ConOpts.set_mqtt_version(MQTTVERSION_DEFAULT);
                // ConOpts.set_connect_timeout(30000);
                // ConOpts.set_keep_alive_interval(60);
                // ConOpts.set_automatic_reconnect(true);

                Client.connect(ConOpts)->wait();

                std::cout << "  ...OK" << std::endl;
                connect=1;
            }
            catch (const mqtt::exception &exc) {
                std::cerr << "\n!!!"
                          << exc << exc.get_message() << std::endl;
                std::cout << "\n!!!"
                          << exc << exc.get_message() << std::endl;

                ErrCallBack("mqtt connect");
            }
        }
    }
}

void MqTT::Mqtt::Disconnect() {
    try {
        std::cout << "Disconnecting..." << std::flush;
        Client.disconnect()->wait();
        std::cout << "OK" << std::endl;
    } catch (const mqtt::exception &exc) {
        std::cerr << "\n" << exc << std::endl;
        ErrCallBack("mqtt disconnect");
    }
}


void MqTT::Mqtt::SetHandler(mqtt::async_client::message_handler cb) {
    Client.set_message_callback(cb);
}

void MqTT::Mqtt::SetHandler(mqtt::async_client::connection_handler cb, bool connect_b) {

    if (connect_b) {
        Client.set_connected_handler(cb);

    } else {
        Client.set_connection_lost_handler(cb);
    }

}

MqTT::Mqtt::Mqtt(stClient c) : Client(c.strAddress, c.strId, mqtt::create_options(MQTTVERSION_5)), TopicS{}, ConOpts{},
                               ErrCallBack{} {
    std::cout << "init ID :" << c.strId << std::endl;
    strID = c.strId;


}

void MqTT::Mqtt::SetHandler(mqtt::async_client::disconnected_handler cb) {
    Client.set_disconnected_handler(cb);
}

void MqTT::Mqtt::SetHandler(mqtt::async_client::update_connection_handler cb) {
    Client.set_update_connection_handler(cb);
}

void MqTT::Mqtt::setErrCallBack(const MqTT::ErrHandler &errCallBack) {
    ErrCallBack = errCallBack;
}
