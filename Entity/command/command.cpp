//
// Created by behrang on 12/19/21.
//

#include "command.h"
#include "iostream"

command::command()
{

}

command::~command()
{

}

void command::toJson()
{
    nlohmann::json j;
    j["messageCommand"] = { {"commandId", cmd.i_commandId},
        {"command", cmd.str_command},
        {"response", cmd.str_response}
    };

}

void commandEntity::extract(nlohmann::json j)
{
    i_commandId = j.at("commandId").get<std::string>();
    str_command = j.at("command").get<std::string>();
    if (i_commandId == "connectWifi") {

    } else {
        str_response = j.at("response").get<std::string>();
    }
}

void commandEntity::print()
{
    std::cout << std::boolalpha << "\ncommandId : " << i_commandId
              <<"\ncommand : " << str_command
              <<"\nresponse : " << str_response << std::endl;
}

json commandEntity::toJson()
{
    json j;
    j["messageCommand"] = { {"commandId", i_commandId},
        {"command", str_command},
        {"response", str_response}
    };
    j.push_back({"messageId", "command"});
    return j;
}
