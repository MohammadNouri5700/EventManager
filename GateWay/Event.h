//
// Created by aziz on 21.09.21.
//

#ifndef EVENT_MANAGER_EVENT_H
#define EVENT_MANAGER_EVENT_H
#include <boost/signals2.hpp>
#include <functional>
#include <string>
#include "Data.h"
#include "Node/Tag.h"
#include "ConvertS/OutputNode.h"
#include <nlohmann/json.hpp>
enum class TYPE
{
    Null = 0,
    PRINT,
    MQTT,
    COAP,
    GPS,
    S7,
    CAN,
    MODBUS,
    SNMP,
    COMMAND,
    EDGE,
    UPDATE,
    SEND,
    RECEIVE,
    TIMER,
    WIFI_SCAN,
    WIFI_CON,
    ERROR,
    MQTTNODE
};

using SignalType = boost::signals2::signal<void(Data *, ProtocolS::Tag *)>;
using SignalTypeNode = boost::signals2::signal<void(Data *, OutputNode *)>;

using FunctionType = std::function<void(Data *, ProtocolS::Tag *)>;
using FunctionTypeNode = std::function<void(Data *, OutputNode *)>;

struct Event
{
    boost::shared_ptr<Data> data{}; // TODO: shared_ptr
    ProtocolS::Tag *Destination{};
    OutputNode *DestinationNode{};
    boost::shared_ptr<SignalType> aSignal{new SignalType};
    boost::shared_ptr<SignalTypeNode> nSignal{new SignalTypeNode};
    TYPE type;

    Event() : data(nullptr), Destination() {}
    Event(Data *data) : data(data) {}
    Event(Data *data, TYPE type) : data(data), type(type) {}
    Event(Data *data, TYPE type, ProtocolS::Tag *dest) : data(data), type(type), Destination(dest) {}
    Event(Data *data, TYPE type, OutputNode *dest) : data(data), type(type), DestinationNode(dest) {}
    Event(Data *data, TYPE type, ProtocolS::Tag *dest, FunctionType &f) : data(data), type(type), Destination(dest)
    {
        aSignal->connect(f);
    }
    void Run()
    {
        (*aSignal)(data.get(), Destination);
    };
    void RunNode()
    {
        (*nSignal)(data.get(), DestinationNode);
    };
    void SetSignal(const FunctionType &f);
    void SetSignal(const FunctionTypeNode &f);
    void merge(Event e);
};

using ItreatorType = std::list<Event>::iterator;

#endif // EVENT_MANAGER_EVENT_H
