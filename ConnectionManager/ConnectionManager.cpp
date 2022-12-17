//
// Created by aziz on 09.10.21.
//

#include "ConnectionManager.h"
#include "../Protocols/S7Protocol.h"
#include "../Protocols/MasterProtocol.h"
#include "../Protocols/CanProtocol.h"
#include "../Protocols/GpsProtocol.h"
#include "../Protocols/ServerProtocol.h"
#include "../Protocols/SubscriberProtocol.h"
#include "../Protocols/PublisherProtocol.h"
#include "../Protocols/KeyProtocol.h"
#include "../Protocols/MouseProtocol.h"
#include "../Protocols/CentralProtocol.h"
#include "../GateWay/EventManager.h"
#include "../GateWay/Connection/ConnectionEdge.h"
#include "../GateWay/ConvertS/Convert.h"

#include "../GateWay/Node/GpsTag.h"
#include "../GateWay/Node/MqttTag.h"
#include "../GateWay/Node/S7Tag.h"
#include "../GateWay/Node/Tag.h"
#include "../GateWay/Node/ModBusTag.h"
#include "../GateWay/Node/CoapTag.h"
#include "../GateWay/Node/EdgeTag.h"
#include "../GateWay/Node/CanTag.h"

#include "../GateWay/Node/NodeList.h"
#include "../GateWay/Listener.h"

extern std::vector<Connection*> ConnectionS;
extern std::vector<Convert> ConvertS;
extern std::vector<ProtocolS::Protocol*> ListenerS;
extern ProtocolS::NodeList nodeList;
extern GateWay::LISTENer::Listener ll;
extern GateWay::EVENT::MANAGER::EventManager e_manager;
using mqtt_sub = ProtocolS::Mqtt::SubscriberProtocol;

auto cb_lose = [](const std::string& s)
{
    std::cerr << "*** Connection Lost  ***"<< s << std::endl;
    ERROR::Error err{ERR_MQTT, s, "design connection manager", ERROR::ErrorType::LOGICAL, 6};
    errorManager.AddError(err);
};

auto errHandMqtt = [](std::string /*strErr*/)
{
    ERROR::Error err{ERR_MQTT, "Mqtt err", "debug Mqtt", ERROR::ErrorType::RUN_TIME, 7};
    errorManager.AddError(err);
};
auto errHandS7 = [](std::string strErr)
{
    ERROR::Error err{ERR_S7, strErr, "debug S7", ERROR::ErrorType::RUN_TIME, 7};
    errorManager.AddError(err);
};

void CONNECTION::ConnectionManager::AddConnection(ProtocolS::Protocol* pro)
{
    std::cout<< "Adding new configuration ...... "<< ListenerS.size() << std::endl;
    std::cout<< "ListenerS.size() " << ListenerS.size()<< std::endl;
    ProtocolS::Tag* tagnew = *(pro->Observer.begin());

    int Counter = 0;
    for(Counter = 0 ;Counter < ListenerS.size() ; Counter++){
        ProtocolS::Tag* tagsystem = *(ListenerS.at(Counter)->Observer.begin());
        std::cout<< "tagsystem->TagType =" << static_cast<int>(tagsystem->TagType)  << std::endl;
        std::cout<< "tagnew->TagType =" << static_cast<int>(tagnew->TagType)  << std::endl;
        if(tagsystem->TagType == tagnew->TagType){
            switch ( tagsystem->TagType)
            {
            case ProtocolIIOT::S7 :
                dynamic_cast<ProtocolS::S7::S7Protocol*>(ListenerS.at(Counter))->Stop();
                ListenerS.at(Counter)->Observer.clear();
                std::cout<< "Found the listener to update ......" << std::endl;
                ListenerS.erase(ListenerS.begin() + Counter);
                break;
             case ProtocolIIOT::MODBUS :
                dynamic_cast<ProtocolS::ModBus::MasterProtocol*>(ListenerS.at(Counter))->Stop();
                ListenerS.at(Counter)->Observer.clear();
                std::cout<< "Found the listener to update ......" << std::endl;
                ListenerS.erase(ListenerS.begin() + Counter);
                break;
            case ProtocolIIOT::MQTT :
                dynamic_cast<ProtocolS::Mqtt::SubscriberProtocol*>(ListenerS.at(Counter))->Stop();
                ListenerS.at(Counter)->Observer.clear();
                std::cout<< "Found the listener to update ......" << std::endl;
                ListenerS.erase(ListenerS.begin() + Counter);
                break;
            case ProtocolIIOT::GPS :
                dynamic_cast<ProtocolS::GPS::GpsProtocol*>(ListenerS.at(Counter))->Stop();
                ListenerS.at(Counter)->Observer.clear();
                std::cout<< "Found the GPS listener to update ......" << std::endl;
                ListenerS.erase(ListenerS.begin() + Counter);
            break;
            default:
                break;
            }
            
        }
    }
    
    std::cout<< "ListenerS.size() " << ListenerS.size()<< std::endl;
    ListenerS.push_back(pro);
    std::cout<< "ListenerS.size() " << ListenerS.size()<< std::endl;
    ll.SetNodes(pro);


}

void CONNECTION::ConnectionManager::AddConvert(Convert Conn)
{
    std::cout<< "Adding new Convert:" << Conn.source() << std::endl;
    ConvertS.push_back(Conn);
}


void CONNECTION::ConnectionManager::Create()
{
    for (auto p:ConnectionS) {

        switch (p->IProtocol) {
            case ProtocolIIOT::CAN : {
            std::cout << "config can" << std::endl;
            auto m = reinterpret_cast<ConnectionCAN*>(p);
            ProtocolS::CAN::CANProtocol *can{new ProtocolS::CAN::CANProtocol(m)};
            can->Create(m);

            ProtocolS::Node n;
            n.first = m->Name.Value;
            for (auto t : m->NodeS ) {
                auto mq = reinterpret_cast<xmlCAN*>(t);
                ProtocolS::CANTag* mn{new ProtocolS::CANTag(mq)};
                mn->conn = m;
                n.second.push_back(mn);
            }
            nodeList.push_back(std::move(n));
            for (auto [i, n]:nodeList) {
                if (strcmp(i.c_str(), m->Name.Value.c_str())==0)
                    for (auto t:n) {
                        t->setSubject(can);
                        t->TagType = ProtocolIIOT::CAN;
                    }
            };
            ListenerS.push_back(can);
        }
        break;
        case ProtocolIIOT::S7 : {
            std::cout << "config S7" << std::endl;
            auto m = reinterpret_cast<ConnectionS7*>(p);
            ProtocolS::S7::S7Protocol *s7{new ProtocolS::S7::S7Protocol};
            s7->setErrCallBack(errHandS7);
            s7->Create(m);

            ProtocolS::Node n;
            n.first = m->Name.Value;
            for (auto t : m->NodeS ) {
                auto mq = reinterpret_cast<xmlS7*>(t);
                ProtocolS::S7Tag* mn{new ProtocolS::S7Tag(mq)};
                mn->conn = m;
                n.second.push_back(mn);
            }
            nodeList.push_back(std::move(n));
            for (auto [i, n]:nodeList) {
                if (strcmp(i.c_str(), m->Name.Value.c_str())==0)
                    for (auto t:n) {
                        t->setSubject(s7);
                        t->TagType = ProtocolIIOT::S7;
                    }
            };
            ListenerS.push_back(s7);
        }
        break;
        case ProtocolIIOT::EDGE : {
            // std::cout << "config Edge" << std::endl;
            // auto m = reinterpret_cast<ConnectionEdge*>(p);
            // ProtocolS::CentralProtocol *central{new ProtocolS::CentralProtocol};
            // central->Create(m);

            // ProtocolS::Node n;
            // n.first = m->Name.Value;
            // for (auto t : m->NodeS ) {
            //     auto mq = reinterpret_cast<xmlEdge*>(t);
            //     ProtocolS::EdgeTag* mn{new ProtocolS::EdgeTag(mq)};

            //     n.second.push_back(mn);
            // }
            // nodeList.push_back(std::move(n));
            // for (auto [i, n]:nodeList) {
            //     if (strcmp(i.c_str(), m->Name.Value.c_str())==0)
            //         for (auto t:n) {
            //             t->setSubject(central);
            //             t->TagType = ProtocolIIOT::EDGE;
            //         }
            // };
            // ListenerS.push_back(central);


        }
        break;
        case ProtocolIIOT::MQTT : {
            std::cout << "config MQTT" << std::endl;
            auto m = reinterpret_cast<ConnectionMqtt*>(p);
            mqtt_sub *node{new mqtt_sub{m}};
            node->setErrCallBack(errHandMqtt);

            // node->SetHandler(cb_lose,false);

            ProtocolS::Node n;
            n.first = m->Name.Value;
            for (auto t : m->NodeS ) {
                auto mq = reinterpret_cast<xmlMqtt*>(t);
                ProtocolS::MqttTag* mn{new ProtocolS::MqttTag(mq)};
                mn->conn = m;
                n.second.push_back(mn);
            }
            nodeList.push_back(std::move(n));

            for (auto [i,n]:nodeList) {
                if(strcmp(i.c_str(),m->Name.Value.c_str())==0)
                    for (auto t:n) {
                        t->setSubject(node);
                        t->TagType = ProtocolIIOT::MQTT;
                    }
            };
            ListenerS.push_back(node);
        }
        break;
        case ProtocolIIOT::MODBUS : {
            std::cout << "config Modbus" << std::endl;
            auto m = reinterpret_cast<ConnectionModbus*>(p);
            ProtocolS::ModBus::MasterProtocol *master{new ProtocolS::ModBus::MasterProtocol()};
            master->Create(m);

            ProtocolS::Node n;
            n.first = m->Name.Value;
            for (auto t : m->NodeS ) {
                auto mq = reinterpret_cast<xmlModBus*>(t);
                ProtocolS::ModBusTag* mn{new ProtocolS::ModBusTag(mq)};
                mn->conn = m;
                n.second.push_back(mn);
            }
            nodeList.push_back(std::move(n));

            for (auto [i,n]:nodeList) {
                if(strcmp(i.c_str(),m->Name.Value.c_str())==0)
                    for (auto t:n) {
                        t->setSubject(master);
                        t->TagType = ProtocolIIOT::MODBUS;
                    }
            };
            ListenerS.push_back(master);
        }
        break;
        case ProtocolIIOT::GPS : {
            // auto ConGPS = reinterpret_cast<ConnectionGPS*>(p);
            // GPs::GpsProtocol *gps{new GPs::GpsProtocol(ConGPS)};
            // gps->setGpsCb(gps_cb02);
            // ListenerS.push_back(gps);
            // std::cout << "\nGPS from connection manager";
            std::cout << "config GPS" << std::endl;
            auto m = reinterpret_cast<ConnectionGPS*>(p);

            ProtocolS::GPS::GpsProtocol *gps{new  ProtocolS::GPS::GpsProtocol(m)};
            gps->Create(m);
            ProtocolS::Node n;
            n.first = m->Name.Value;
            for (auto t : m->NodeS ) {
                auto mq = reinterpret_cast<xmlGPS*>(t);
                ProtocolS::GPSTag* mn{new ProtocolS::GPSTag(mq)};
                mn->conn = m;
                n.second.push_back(mn);
            }
            nodeList.push_back(std::move(n));
            for (auto [i, n]:nodeList) {
                if (strcmp(i.c_str(), m->Name.Value.c_str())==0)
                    for (auto t:n) {
                        t->setSubject(gps);
                        t->TagType = ProtocolIIOT::GPS;
                    }
            };

            ListenerS.push_back(gps);
//        }
//            std::cout << "config GPS" << std::endl;
//            auto m = reinterpret_cast<ConnectionGPS*>(p);
//            ProtocolS::GPS::GpsProtocol *gps{new ProtocolS::GPS::GpsProtocol};
////            s7->setErrCallBack(errHandS7);
//            gps->Create(m);
//
//            ProtocolS::Node n;
//            n.first = m->Name.Value;
//            for (auto t : m->NodeS ) {
//                auto mq = reinterpret_cast<xmlGPS*>(t);
//                ProtocolS::GPSTag* mn{new ProtocolS::GPSTag(mq)};
//                mn->conn = m;
//                n.second.push_back(mn);
//            }
//            nodeList.push_back(std::move(n));
//            for (auto [i, n]:nodeList) {
//                if (strcmp(i.c_str(), m->Name.Value.c_str())==0)
//                    for (auto t:n) {
//                        t->setSubject(gps);
//                        t->TagType = ProtocolIIOT::GPS;
//                    }
//            };
//            ListenerS.push_back(gps);
        }
        break;
        case ProtocolIIOT::SNMP : {

            /* using namespace ProtocolS::SnMP;
             SnmpProtocol* snmp{new SnmpProtocol()};
             snmp->SetConnection(p);
             snmp->SetType(SNMPpp::PDU::kGet);
             snmp->SetPduCb(pdu_h);
             snmp->SetActCallback(act_h);
             ListenerS.push_back(snmp);*/
            std::cout << "SNMP";
        }
        break;
        case ProtocolIIOT::COAP : {
            /*using namespace ProtocolS::COAP;
            auto m = reinterpret_cast<ConnectionCoap*>(p);
            ServerProtocol* node{new ServerProtocol};
            node->Create(p);

            ProtocolS::Node n;
            n.first = m->Name.Value;
            for (auto t : m->NodeS ) {
               auto mq = reinterpret_cast<xmlCoap*>(t);
               ProtocolS::CoapTag* mn{new ProtocolS::CoapTag(mq)};
               n.second.push_back(mn);
            }
            nodeList.push_back(std::move(n));

            for (auto [i,n]:nodeList) {
               if(strcmp(i.c_str(),m->Name.Value.c_str())==0)
                   for (auto t:n) {
                       t->setSubject(node);
                   }
            };
            node->Open(Connection *Conn);
            p->print();
            ListenerS.push_back(node);*/
            std::cout << "\ncoap";
        }

        break;
        default:
            std::cout << "\ncheck type connection";
            break;
        }
        std::cout <<"\n................................................\n";
    }    


}