//
// Created by MohammadNouri on 12.10.22.
//


#include "GpsTag.h"
#include "../GateWay/ConvertS/Convert.h"
#include "../Event.h"
#include "../GateWay/Node/NodeList.h"
#include "atomic_queue/atomic_queue.h"
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using Queue = atomic_queue::AtomicQueueB2<Event>; // Use heap-allocated buffer.
extern Queue EventList;
extern std::vector<Convert> ConvertS;


using namespace boost;

void ProtocolS::GPSTag::SendEvent()
{
    Event b;

    std::string str((char *)Value);

    this->jsonvalue =str;


    Event e{new ProtocolData{str, nullptr,Name.Value}, TYPE::PRINT};

    auto size = strlen(str.c_str());
    free(Value);
    Value = malloc(size + 1);
    memset(Value, 0, size + 1);
    // if (memcmp((Byte*)Value, (Byte*)value, Size) != 0) {
    memmove(Value, str.c_str(), size);
    for (auto p : ConvertS)
    {
        std::cout << "Convert Source :" << p.source() << std::endl;
        std::cout << "Convert Dest :" << p.distS()[0].c_str() << std::endl;
        if (p.source() == this->Name.Value)
        {
            auto t = findTag(p.distS()[0]);
            if (t == nullptr)
                continue;
            switch (t->conn->IProtocol)
            {
                case ProtocolIIOT::MQTT:
                {
//                    json temp;
//                    if (t->ValueType.Value == "Json")
//                    {
//                        temp = json{{t->Name.Value, str}};
//                    }
//                    str = temp.dump();
                    t->setValue((void *)str.c_str(), strlen(str.c_str()));
                    if (!t->OnlyNode)
                    {
                        std::cout << "public Tag" << t->Name.Value << std::endl;
                        b = Event(new ProtocolData{str, Value,Name.Value}, TYPE::MQTT, t);
                        EventList.push(std::move(b));
                    }
                    else
                        std::cout << "private Tag" << t->Name.Value << std::endl;
                }
                    break;
                case ProtocolIIOT::S7:
                    b = Event(new ProtocolData{str, Value,Name.Value}, TYPE::S7, t);
                    EventList.push(std::move(b));
                    break;
                case ProtocolIIOT::MODBUS:
                    b = Event(new ProtocolData{str, Value,Name.Value}, TYPE::MODBUS, t);
                    EventList.push(std::move(b));
                    break;
                default:
                    break;
            }
        }
    }
    EventList.push(std::move(e));
}

void ProtocolS::GPSTag::Print()
{
     
    std::cout << "$$$$$$$$$$$$$$$$ Print Print Print $$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
}


void ProtocolS::GPSTag::UpdateValue()
{
}

ProtocolS::GPSTag::~GPSTag()
{
   Tag::Print();
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
}

int ProtocolS::GPSTag::GetType()
{
return 10;
}

void ProtocolS::GPSTag::setSubject(Protocol * subject)
{
    Tag::setSubject(subject);
}

ProtocolS::GPSTag::GPSTag(xmlGPS * gps): Tag(gps) {}

void ProtocolS::GPSTag::setValue(void *value, size_t Size) {
    Tag::setValue(value, Size);
}
