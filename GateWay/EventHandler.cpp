/*! \brief this object handles all events. Event will handle according
 *         Brief description continued.
 *
 *  Detailed description starts here.
 */
#include "EventHandler.h"
#include <ctime>
#include <chrono>
#include <iostream>

extern std::mutex end_mutex;

GateWay::EVENT::HANDLER::EventHandler::EventHandler()
{
}

GateWay::EVENT::HANDLER::EventHandler::~EventHandler()
{
}
auto as_integer(TYPE const value)
-> typename std::underlying_type<TYPE>::type
{
    return static_cast<typename std::underlying_type<TYPE>::type>(value);
}

std::mutex EventMutex;

void GateWay::EVENT::HANDLER::EventHandler::Act()
{
    std::cout << "void GateWay::EVENT::HANDLER::EventHandler::Act()" << std::endl;
    auto free_b = [this]() {
        EventMutex.lock();
        std::vector<Event> merged_events;
        /* Merge events to reduce transations */
        while (!EventList.was_empty()) {
            std::cout << "free_b========----------------------------"
                      << "\n";
            auto it = EventList.pop();
            auto n = merged_events.size();
            if (n == 0 || it.Destination == NULL) {
                merged_events.push_back(it);
                continue;
            }
            bool Applied = false;
            for (int i = 0; i < n && !Applied; i++) {
                auto &e = merged_events[i];
                if (e.type == it.type && e.Destination->compare(it.Destination)) {
                    if (e.data->GetString().size()+ it.data->GetString().size() <
                    (e.Destination->conn->iMaxMessageSize.Value ==0 ? 5000 :e.Destination->conn->iMaxMessageSize.Value )) {
                    e.merge(it);
                        Applied = true;
                    }
                }
            }

            if (!Applied) {
                merged_events.push_back(it);
            }
        }
        for (auto &e : merged_events) {
            TYPE t = e.type;
            std::cout << "main switch" << (int)t << "***" << merged_events.size()<< "\n";
            switch (t) {
            case TYPE::MQTT:
                std::cout << "free_b TYPE::MQTT" << std::endl;
                e.SetSignal(MqttCB01);
                break;
            case TYPE::MODBUS:
                e.SetSignal(ModbusCB01);
                break;
            case TYPE::S7:
                e.SetSignal(S7CB01);
                break;
            case TYPE::PRINT:
                // e.SetSignal(PrintCB01);
                break;
            case TYPE::CAN:
                e.SetSignal(CANCB01);
                break;
            case TYPE::MQTTNODE:
                e.SetSignal(MqttCB02);
                break;
            case TYPE::UPDATE:
                e.SetSignal(Updater);
                break;
            // case TYPE::WIFI_SCAN:
            //     e.SetSignal(Wifi_scan);
            //     break;
            // case TYPE::WIFI_CON:
            //     e.SetSignal(wifi_Connect);
            //     break;
            case TYPE::ERROR: {
                /*e.SetSignal(PrintCB01);
                e.SetSignal(Notyfy01);
                e.SetSignal(message01);*/
            }
            break;
            default:
                break;
            }

            if (TYPE::ERROR == e.type) {
                e.SetSignal(PrintCB01);
                e.SetSignal(Notyfy01);
            }
            if (e.type == TYPE::MQTTNODE)
                PoolEvent.Post(std::bind([](Event e) {
                e.RunNode();
            },
            e));
            else
                PoolEvent.Post(std::bind([](Event e) {
                e.Run();
            },
            e));
        }
        merged_events.clear();
        EventMutex.unlock();
    };

    PoolQueue.Post(free_b);
    Caller.push_task("re", std::chrono::microseconds(500), free_b);

    Caller.run();
    PoolEvent.Wait();
    PoolQueue.Wait();
}
