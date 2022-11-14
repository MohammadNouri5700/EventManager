//
// Created by aziz on 29.09.21.
//

#ifndef EVENT_MANAGER_TAG_H
#define EVENT_MANAGER_TAG_H
#include <string>
#include <cstring>
#include <list>



#include "../Connection/Connection.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ProtocolS
{
class Protocol;
class Tag
{
    Protocol *subject{};

    //static int static_number;
    int number{};

public:
    strTag Name{};
    strTag Units{};
    strTag ValueType{};
    strTag Notes{};
    bTag ReadWrite{0};
    bTag Disable{0};
    boost::posix_time::ptime inputTime;
    boost::posix_time::ptime outputTime;
    Second Timer{};
    bool read{false};
    bool write{false};
    bool OnlyNode{false};
    size_t SizeValue{0};
    ProtocolIIOT TagType;
    void* Value{nullptr};
    Connection* conn;

    virtual bool compare(Tag *t) = 0;

    virtual void setValue(void *value, size_t Size);

    virtual void setSubject(Protocol *subject);
    virtual void SendEvent()=0;
    void RemoveFromTheList();
    void setName(const std::string &strName);
    virtual void UpdateValue();
    virtual void Print();
    virtual ~Tag();
    std::string strGetName()
    {
        return Name.Value;
    }
    virtual int GetType() {return 0; /*TODO*/}

    Tag(const strTag &name, const strTag &units, const strTag &valueType, const strTag &notes,
        const bTag &readWrite, const bTag &disable, const Second &time);

    Tag(xmlNode * node);
    Tag(const Tag&) = delete;
    Tag& operator=(const Tag&) = delete;
    Tag(){}
    void setBitValue(bool value);
};
}

#endif //EVENT_MANAGER_TAG_H
