//
// Created by aziz on 21.09.21.
//

#include "Event.h"

void Event::SetSignal(const FunctionType &f)
{
    aSignal->connect(f);
}

void Event::SetSignal(const FunctionTypeNode &f)
{
    nSignal->connect(f);
}

json merge_json(const json &a, const json &b)
{
    json result = a;
    json tmp = b;

    for (json::iterator it = tmp.begin(); it != tmp.end(); ++it) {
        result[it.key()] = it.value();
    }

    return result;
}

void Event::merge(Event e)
{
    switch (e.type) {
    case TYPE::MQTT: {
        std::cout << this->data->GetJson() << "----------------" << e.data->GetJson() << std::endl;
        json j1 = dynamic_cast<ProtocolData *>(this->data.get())->jsonData.empty() ? json::parse(this->data->GetJson()) : dynamic_cast<ProtocolData *>(this->data.get())->jsonData;
        json j2 = dynamic_cast<ProtocolData *>(e.data.get())->jsonData.empty() ? json::parse(e.data->GetJson()) : dynamic_cast<ProtocolData *>(e.data.get())->jsonData;
        j1 = merge_json(j1, j2);
        dynamic_cast<ProtocolData *>(this->data.get())->jsonData = j1;
    }
    std::cout << "===============" << dynamic_cast<ProtocolData *>(this->data.get())->jsonData.dump() << std::endl;
    break;
    case TYPE::S7:
        // this->data = e.data;
        std::cout << this->data->GetString() << "------++++++--------" << e.data->GetString() << std::endl;
        break;
    case TYPE::MODBUS:
        std::cout << this->data->GetString() << "-------======-------" << e.data->GetString() << std::endl;
        break;

    default:
        break;
    }
}
