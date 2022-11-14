//
// Created by aziz on 03.08.21.
//

#ifndef EVENT_MANAGER_SUBSCRIBERPROTOCOL_H
#define EVENT_MANAGER_SUBSCRIBERPROTOCOL_H
#include "../W_mqtt/MqttSubscriber.h"
#include "Protocol.h"
#include "../GateWay/Connection/ConnectionMqtt.h"
#include "../GateWay/Node/MqttTag.h"

namespace ProtocolS::Mqtt
{
    class SubscriberProtocol : public ProtocolS::Protocol, public MqTT::MqttSubscriber
    {
    public:
        SubscriberProtocol();
        SubscriberProtocol(ConnectionMqtt *Conn);
        SubscriberProtocol(const stClient &s);
        virtual ~SubscriberProtocol();
        void Listen() override;
        void Create(Connection *Conn) override;
        void Open(Connection *Conn) override;
        void Close() override;
        void KeepAlive() override;
        bool isOK() override;
        void Reconnect() override;
        void hasError() override;
        void DataReceived() override;
        void UpdateTag(Tag *tag) override;
        void Write(Data *data, Tag *tag) override;
        void Stop();
    };
}

#endif // EVENT_MANAGER_SUBSCRIBERPROTOCOL_H
