//
// Created by aziz on 11.10.21.
//

#include "S7Tag.h"
#include <cstring>
#include "../Event.h"
#include "../GateWay/ConvertS/Convert.h"
#include "../GateWay/Node/NodeList.h"
#include "atomic_queue/atomic_queue.h"

using Queue = atomic_queue::AtomicQueueB2<Event>; // Use heap-allocated buffer.
extern Queue EventList;
extern std::vector<Convert> ConvertS;
using Byte = uint8_t;

void ProtocolS::S7Tag::setSubject(ProtocolS::Protocol *subject)
{
    Tag::setSubject(subject);
}

void ProtocolS::S7Tag::SendEvent()
{
    std::string v;
    Event b;
    std::cout << "void ProtocolS::S7Tag::SendEvent() type == " << ValueType.Value.c_str() << std::endl;

    if (strcmp(ValueType.Value.c_str(), "float")==0) {
        float  Res; memcpy (&Res, Value, 4);
        v = std::to_string(Res);
    }
    else if (strcmp(ValueType.Value.c_str(), "int")==0) {
        v = std::to_string(*((int32_t*)Value));
    }
    else if (strcmp(ValueType.Value.c_str(), "int16")==0) {
        v = std::to_string(*((int16_t*)Value));
    }
    else if (strcmp(ValueType.Value.c_str(), "bool")==0) {
        v = (*((bool*)Value))?"true":"false";
    }
    else if (strcmp(ValueType.Value.c_str(), "byte")==0) {
        v = std::to_string(*((int8_t*)Value));
    }
    Event e{new ProtocolData{v, nullptr,Name.Value}, TYPE::PRINT};
    for (auto p: ConvertS) {
        if (p.source() == this->Name.Value) {
            auto t = findTag(p.distS()[0]);
           
            switch (t->conn->IProtocol)
            {
            case ProtocolIIOT::MQTT:
            {
                //json temp;
                //if (t->ValueType.Value == "Json")
                //{
                    //temp = json{t->Name.Value , v };
                    //v = "\"" +t->Name.Value + "\":\"" + v +"\"";

                //}
                //v = temp.dump();
                t->setValue((void *)v.c_str(), strlen(v.c_str()));
                if (!t->OnlyNode)
                {
                    std::cout << "public Tag" << t->Name.Value << std::endl;
                    b = Event(new ProtocolData{v, Value,Name.Value}, TYPE::MQTT, t);
                    EventList.push(std::move(b));
                }
                else{
                    std::cout << "private Tag" << t->Name.Value << std::endl;
                }
            }
            break;

            case ProtocolIIOT::MODBUS:
                b = Event(new ProtocolData{v,Value,Name.Value}, TYPE::MODBUS, t);
                EventList.push(std::move(b));
                break;

            case ProtocolIIOT::CAN:
                b = Event(new ProtocolData{v,Value,Name.Value}, TYPE::CAN, t);
                EventList.push(std::move(b));
                break;
                
            default:
                break;
            }
        }
    }
    EventList.push(std::move(e));
}

void ProtocolS::S7Tag::Print()
{
    Tag::Print();
   
}

ProtocolS::S7Tag::~S7Tag()
{

}

ProtocolS::S7Tag::S7Tag(xmlS7 * nS7): Tag(nS7), StartingAddress(nS7->StartingAddress), BitNumber(nS7->BitNumber),SignalState(nS7->SignalState),s7tagType(nS7->s7TagType) ,DBNumber(nS7->DBNumber) {}

uint16_t ProtocolS::S7Tag::getStartingAddress() const
{
    return StartingAddress.Value;
}

uint16_t  ProtocolS::S7Tag::getBitNumber() const
{
    return BitNumber.Value;
}

uint16_t  ProtocolS::S7Tag::getDBNumber() const
{
    return DBNumber.Value;
}

bool ProtocolS::S7Tag::getSignalState() const
{
    return SignalState.Value;
}

void ProtocolS::S7Tag::UpdateValue()
{
    Tag::UpdateValue();
}

int ProtocolS::S7Tag::GetType()
{
    int v = 0;
    if (strcmp(ValueType.Value.c_str(), "float") == 0)
    {
        v = 4;
    }
    else if (strcmp(ValueType.Value.c_str(), "int") == 0)
    {
        v = 4;
    }
    else if (strcmp(ValueType.Value.c_str(), "int16") == 0)
    {
        v = 2;
    }
    else if (strcmp(ValueType.Value.c_str(), "bool") == 0)
    {
        v = 0;
    }
    else if (strcmp(ValueType.Value.c_str(), "byte") == 0)
    {
        v = 1;
    }
    return v;
}



