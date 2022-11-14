//
// Created by behrang on 12/18/21.
//

#ifndef EVENT_MANAGER_JSONMESSAGE_H
#define EVENT_MANAGER_JSONMESSAGE_H
#include <istream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct JsonMessage {
    virtual ~JsonMessage(){}
    virtual void extract(nlohmann::json j) = 0;
    virtual json toJson() {/*TODO*/ return json{};}
    virtual void print() = 0 ;
};

#endif //EVENT_MANAGER_JSONMESSAGE_H
