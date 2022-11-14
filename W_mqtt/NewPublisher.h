//
// Created by aziz on 18.09.21.
//

#ifndef EVENT_MANAGER_NEWPUBLISHER_H
#define EVENT_MANAGER_NEWPUBLISHER_H
#include "MqttPublisher.h"

namespace MqTT
{
class NewPublisher: public MqttPublisher
{
public:
    void Run() override;
    NewPublisher(const std::string &addr, const std::string &id);

};
}


#endif //EVENT_MANAGER_NEWPUBLISHER_H
