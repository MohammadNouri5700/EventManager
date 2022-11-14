//
// Created by aziz on 07.08.21.
//

#ifndef EVENT_MANAGER_SIGNALS_H
#define EVENT_MANAGER_SIGNALS_H
#include <any>
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <mutex>
#include <thread>
#include <sstream>
#include "../W_mqtt/MqttPublisher.h"
#include "../W_mqtt/NewPublisher.h"

#include <fstream>
#include "Event.h"

using ItreatorType = std::list<Event>::iterator;

struct BlockType
{
    ItreatorType aBegin;

    ItreatorType aEnd;
    size_t aNum;
    BlockType(const ItreatorType &b, const ItreatorType &e, const size_t n) : aBegin(b), aEnd(e), aNum(n) {}
    BlockType() = delete;
};

namespace
{
    std::mutex g_i_mutex;
    std::mutex sender;
}

extern FunctionType MqttCB01;
extern FunctionType ModbusCB01;
extern FunctionType S7CB01;
extern FunctionType CANCB01;
extern FunctionType PrintCB01;
extern FunctionType Notyfy01;
extern FunctionType message01;
extern FunctionTypeNode MqttCB02;

extern FunctionType Updater;
extern FunctionType PIPE_W;

extern FunctionType PIPE_W_j;

extern FunctionType Fnp2Protocols;

// extern FunctionType Wifi_scan;
// extern FunctionType wifi_Connect;

#endif // EVENT_MANAGER_SIGNALS_H
