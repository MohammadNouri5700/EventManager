//
// Created by behrang on 12/20/21.
//

#ifndef EVENT_MANAGER_TAGVALUE_H
#define EVENT_MANAGER_TAGVALUE_H

#include <string>
#include <nlohmann/json.hpp>
#include "../JsonMessage.h"

struct tagValueEntity:public JsonMessage {
    int tagId{0};
    std::string tagsRef{""};
    std::string dateTime{""};
    std::string tagsValue{""};

    void extract(nlohmann::json j) override;
    void print() override;
};

class tagvalue
{
public :
    tagvalue();
    virtual ~tagvalue();
    void toJson();
private:
    tagValueEntity cmd{};
};


#endif //EVENT_MANAGER_TAGVALUE_H
