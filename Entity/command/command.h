//
// Created by behrang on 12/19/21.
//

#ifndef EVENT_MANAGER_COMMAND_H
#define EVENT_MANAGER_COMMAND_H

#include <string>
#include <nlohmann/json.hpp>
#include "../JsonMessage.h"

struct commandEntity:public JsonMessage {
    std::string i_commandId{""};
    std::string str_command{""};
    std::string str_response{""};


    void extract(nlohmann::json j) override;
    void print() override;

    json toJson() override;
};

class command
{
public :
    command();
    virtual ~command();
    void toJson();
private:
    commandEntity cmd{};
};

#endif //EVENT_MANAGER_COMMAND_H
