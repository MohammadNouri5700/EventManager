//
// Created by behrang on 12/20/21.
//

#ifndef EVENT_MANAGER_GETTAGVALUE_H
#define EVENT_MANAGER_GETTAGVALUE_H


#include <string>
#include <nlohmann/json.hpp>
#include "../JsonMessage.h"

struct gettagValueEntity:public JsonMessage {
    int tagId{0};
    int tagsRef{0};
    std::string dateTime{""};
    std::string tagsValue{""};

    gettagValueEntity(int tagId, int tagsRef, const std::string &dateTime, const std::string &tagsValue);

    json toJson() override;

    void extract(nlohmann::json j) override;
    void print() override;
};

class gettagvalue
{
public :
    gettagvalue();
    virtual ~gettagvalue();
    void toJson();
private:
    gettagValueEntity cmd;
};

#endif //EVENT_MANAGER_GETTAGVALUE_H
