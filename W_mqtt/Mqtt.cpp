#include "Mqtt.h"

//class mqtt_client_callback : public virtual mqtt::callback,
//                             public virtual mqtt::iaction_listener {
//
//
//    void message_arrived(mqtt::const_message_ptr msg) override {
//
//    }
//
//
//    void connected(const std::string &cause) override {
//
//    }
//};
//
//class subscription_callback : public virtual mqtt::iaction_listener {
//
//
//    void on_failure(const mqtt::token &tok) override {
//
//    }
//
//
//    void on_success(const mqtt::token &tok) override {
//
//    }
//
//};


MqTT::Mqtt::Mqtt(std::string address, std::string id) : Client(address, id, mqtt::create_options(MQTTVERSION_3_1)),
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
//        if (TopicS.size()) {
//            Connect();
            Act();
//            Disconnect();
//        }
    }
    catch (const mqtt::exception &exc) {
        std::cerr << "\n!@!" << exc << std::endl;
        ErrCallBack("mqtt Run");
    }
}

void MqTT::Mqtt::Connect(bool publisher) {
    if (Client.is_connected())
        return;

    int connect = 0;
    while (connect == 0) {


        try {
            std::cout << "--MQTT" << std::endl;
            std::cout << "\nConnecting... '" << Client.get_server_uri() << " " << Client.get_client_id()
                      << std::endl;
            ConOpts.set_clean_session(false);
            ConOpts.set_mqtt_version(MQTTVERSION_3_1);
            ConOpts.set_connect_timeout(30000);
//            ConOpts.set_automatic_reconnect(true);
            ConOpts.set_keep_alive_interval(10);
            ConOpts.set_automatic_reconnect(true);

            Client.connect(ConOpts)->wait();


            // Client.subscribe(TopicS.front().name_,0);

            // Client.start_consuming();

            // mqtt::const_message_ptr messagePointer;
            // if(Client.try_consume_message(&messagePointer)){}


            std::cout << "  Connection ...OK try_consume_message" << std::endl;


            connect = 1;
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

void MqTT::Mqtt::Disconnect() {
//    try {
//        std::cout << "Disconnecting..." << std::flush;
//        Client.disconnect()->wait();
//        std::cout << "OK" << std::endl;
//    } catch (const mqtt::exception &exc) {
//        std::cerr << "\n" << exc << std::endl;
//        ErrCallBack("mqtt disconnect");
//    }
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

MqTT::Mqtt::Mqtt(stClient c) : Client(c.strAddress, c.strId, mqtt::create_options(MQTTVERSION_3_1)), TopicS{},
                               ConOpts{},
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

bool MqTT::Mqtt::findclient(std::string address) {
    for (int i = 0; i < connectors.size(); ++i) {
        if (std::strcmp(connectors[i].get_client_id().c_str(), address.c_str()) == 1) {
            return connectors[i].is_connected();
        }
    }
}



























