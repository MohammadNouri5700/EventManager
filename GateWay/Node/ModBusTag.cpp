//
// Created by aziz on 12.10.21.
//

#include "ModBusTag.h"
#include "../Event.h"
#include "../GateWay/ConvertS/Convert.h"
#include "../GateWay/Node/NodeList.h"
#include "atomic_queue/atomic_queue.h"

using Queue = atomic_queue::AtomicQueueB2<Event>; // Use heap-allocated buffer.
extern Queue EventList;
extern std::vector<Convert> ConvertS;
void ProtocolS::ModBusTag::setSubject(ProtocolS::Protocol *subject)
{
    Tag::setSubject(subject);
}

void ProtocolS::ModBusTag::SendEvent()
{
    //std::string *str = reinterpret_cast<std::string*>(Value); // TODO: dont send or receive c++ string, sends its data.
    std::string v;
    Event b;
    std::cout << "void ProtocolS::ModBusTag::SendEvent()" << std::endl;
    if (strcmp(ValueType.Value.c_str(), "float")==0) {
        float  Res; memcpy (&Res, Value, 4);
        v = std::to_string(Res);
    }
    else if (strcmp(ValueType.Value.c_str(), "int")==0) {
        v = std::to_string(*((int32_t*)Value));

    }
    else if (strcmp(ValueType.Value.c_str(), "int16")==0) {
        v = std::to_string(*((int16_t*)Value));
        std::cout << "Value Type :" << "int16_t" << std::endl;

    }
    else if (strcmp(ValueType.Value.c_str(), "bool")==0) {
        v = (*((bool*)Value))?"true":"false";
    }
     else if (strcmp(ValueType.Value.c_str(), "byte")==0) {
        v = std::to_string(*((int8_t*)Value));
    }
    Event e{new ProtocolData{v, nullptr,Name.Value}, TYPE::PRINT};
    for (auto p : ConvertS)
    {
        // std::cout << "Convert Source :" << p.source() << std::endl;
        // std::cout << "Convert Dest :" << p.distS()[0].c_str() << std::endl;
        // std::cout << "Convert Value :" << v << std::endl;
        if (p.source() == this->Name.Value)
        {
            auto t = findTag(p.distS()[0]);
            switch (t->conn->IProtocol)
            {
            case ProtocolIIOT::MQTT:
            {
                json temp;
                if (t->ValueType.Value == "Json")
                {
                    temp = json{{t->Name.Value , v }};
                }
                v = temp.dump();
                t->setValue((void *)v.c_str(), strlen(v.c_str()));
                if (!t->OnlyNode)
                {
                    std::cout << "public Tag" << t->Name.Value << std::endl;
                    b = Event(new ProtocolData{v, Value,Name.Value}, TYPE::MQTT, t);
                    EventList.push(std::move(b));
                }
                else
                    std::cout << "private Tag" << t->Name.Value << std::endl;
                }
                break;
            case ProtocolIIOT::S7:
                b = Event(new ProtocolData{v, Value,Name.Value}, TYPE::S7, t);
                EventList.push(std::move(b));
                break;
            case ProtocolIIOT::MODBUS:
                b = Event(new ProtocolData{v, Value,Name.Value}, TYPE::MODBUS, t);
                EventList.push(std::move(b));
                break;
            default:
                break;
            }
        }
    }
    EventList.push(std::move(e));
}

void ProtocolS::ModBusTag::Print()
{
    Tag::Print();
    std::cout << "Starting Address :" << StartingAddress.Value <<"\n"
              << "Number Of Registers :" << NumberOfRegisters.Value <<"\n"
              << "Scale : " << Scale.Value <<"\n"
              << "Function : " << Function.Value <<"\n";
}

ProtocolS::ModBusTag::ModBusTag(xmlModBus *node) : Tag(node), StartingAddress(node->StartingAddress), NumberOfRegisters(node->NumberOfRegisters),
    Scale(node->Scale), Function(node->Function) {}

// ProtocolS::ModBusTag::ModBusTag( uint16_t startingAddress, uint16_t numberOfRegisters, uint16_t scale,uint16_t function) : Tag()


// }


uint16_t ProtocolS::ModBusTag::getStartingAddress() const
{
    return StartingAddress.Value;
}

uint16_t ProtocolS::ModBusTag::getNumberOfRegisters() const
{
    return NumberOfRegisters.Value;
}

uint16_t ProtocolS::ModBusTag::getScale() const
{
    return Scale.Value;
}

uint16_t ProtocolS::ModBusTag::getFunction() const
{
    return Function.Value;
}

void ProtocolS::ModBusTag::setStartingAddress(uint16_t startingAddress) 
{
    StartingAddress.Value = startingAddress;
}

void ProtocolS::ModBusTag::setNumberOfRegisters(uint16_t numberOfRegisters) 
{
    NumberOfRegisters.Value = numberOfRegisters;
}

void ProtocolS::ModBusTag::setScale(uint16_t scale) 
{
    Scale.Value = scale;
}

void ProtocolS::ModBusTag::setFunction(uint16_t function) 
{
    Function.Value = function;
}


void ProtocolS::ModBusTag::UpdateValue()
{
    Tag::UpdateValue();
}

ProtocolS::ModBusTag::~ModBusTag()
{

}

int ProtocolS::ModBusTag::GetType()
{
    return 8;
}

