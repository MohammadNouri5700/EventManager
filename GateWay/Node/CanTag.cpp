//
// Created by aziz on 08.10.21.
//

#include "CanTag.h"
#include "../../Protocols/CanProtocol.h"
#include "../GateWay/ConvertS/Convert.h"
#include "../Event.h"
#include "../GateWay/Node/NodeList.h"
#include "atomic_queue/atomic_queue.h"
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using Queue = atomic_queue::AtomicQueueB2<Event>; // Use heap-allocated buffer.
extern Queue EventList;
extern std::vector<Convert> ConvertS;

using RecCAN = ProtocolS::CAN::CANProtocol;

int ProtocolS::CANTag::SbitExtracted(int number, int k, int p)
{
    return (((1 << k) - 1) & (number >> (p - 1)));
}

using namespace std;
using namespace boost;

void ProtocolS::CANTag::SendEvent()
{
    Event b;

    std::string str((char *)Value);
    data = atoi((char *)Value);
    std::cout << "Can value : " << str << std::endl;
    Event e{new ProtocolData{str, nullptr,Name.Value}, TYPE::PRINT};
    char_separator<char> sep(" ");
    tokenizer<char_separator<char>> tokens(str, sep);
    int byte_no = BitNumber.Value / 8;
    int bit_no = BitNumber.Value % 8;
    int counter = 0;
    int value = 0;
    int bit_count = BitCount.Value;
    BOOST_FOREACH (const string &t, tokens)
    {
        if (counter == byte_no)
        {
            value *= 256;
            value += stoi(t);
            if (bit_count <= 8)
                break;
            else
                bit_count -= 8;
            byte_no++;
        }
        counter++;
    }
    value = SbitExtracted(value, BitCount.Value, bit_no);
    str = std::to_string(value);

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
                json temp;
                if (t->ValueType.Value == "Json")
                {
                    temp = json{{t->Name.Value, str}};
                }
                str = temp.dump();
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

void ProtocolS::CANTag::Print()
{
    Tag::Print();
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
}

void ProtocolS::CANTag::setSubject(ProtocolS::Protocol *subject)
{
    Tag::setSubject(subject);
}

ProtocolS::CANTag::CANTag(xmlCAN *can) : Tag(can)
{
    StartingAddress = can->StartingAddress;
    BitNumber = can->BitNumber;
    CANID = can->CANID;
    BitCount = can->BitCount;
}

void ProtocolS::CANTag::UpdateValue()
{
    Tag::UpdateValue();
}

ProtocolS::CANTag::~CANTag()
{
}

int ProtocolS::CANTag::GetType()
{
    return 9;
}
