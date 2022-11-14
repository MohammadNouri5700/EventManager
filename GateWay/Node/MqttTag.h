//
// Created by aziz on 08.10.21.
//

#ifndef EVENT_MANAGER_MQTTTAG_H
#define EVENT_MANAGER_MQTTTAG_H

#include "Tag.h"
#include "../Connection/ConnectionMqtt.h"
namespace ProtocolS
{
class MqttTag : public Tag
{
private:
    int data;
protected:
    void SendEvent() override;
public:
    strTag Topic;
    strTag Prefix;
    ClientActions clientAction;
    //strTag MessageType;
    void Print() override;

    void UpdateValue() override;

    ~MqttTag() override;

    int GetType() override;

    void setSubject(Protocol *subject) override;

    MqttTag(xmlMqtt* mqtt);

    virtual bool compare(Tag *t)
    {
        auto tag = dynamic_cast<MqttTag*>(t);
        if (tag == NULL) {
            return false;
        }
        return this->Topic.Value == tag->Topic.Value && this->conn->Address.Value == tag->conn->Address.Value;
    }
};

}


#endif //EVENT_MANAGER_MQTTTAG_H
