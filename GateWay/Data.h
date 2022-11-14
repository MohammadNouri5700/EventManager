//
// Created by aziz on 21.09.21.
//

#ifndef EVENT_MANAGER_DATA_H
#define EVENT_MANAGER_DATA_H
#include <string>
#include <sstream>
#include "../ErrorManager/Error.h"
#include "Node/Tag.h"
#include "../Entity/JsonMessage.h"

struct Data {
    virtual std::string GetString()=0;
    virtual std::string GetJson()=0;
    void* data;
    std::string dataName;

    virtual ~Data() {};
};



struct ProtocolData : public Data {
    std::string stringData;
    json jsonData;
    ProtocolData(const std::string &stringData, void *data_ ,   std::string dataName_) : stringData(stringData) {
        data = data_;
        dataName = dataName_;
    }

    virtual ~ProtocolData() { }

    std::string GetString() override
    {
        return stringData;
    }

    std::string GetJson() override
    {
        return json{{dataName , stringData} }.dump();
    }
    
};

struct ErrorData : public Data {
    ERROR::Error errData;

    ErrorData(const ERROR::Error &errData) : errData(errData) {}

    virtual ~ErrorData() { }

    std::string GetString() override
    {
        std::stringstream ss;
        ss << errData;
        return ss.str();
    }

    std::string GetJson() override
    {
        return "";
    }
};
struct Command : public Data {

};

struct TagData : public Data {

    ProtocolS::Tag *tag_;

    TagData(ProtocolS::Tag *tag) : tag_(tag) {}
    virtual ~TagData() {}
    TagData(const TagData&) = delete;
    TagData operator=(const TagData&) = delete;

    std::string GetString() override
    {
        return tag_->strGetName();
    };

    std::string GetJson() override
    {
        return json{{ dataName , tag_->strGetName() }}.dump();
    }
};


#endif //EVENT_MANAGER_DATA_H



