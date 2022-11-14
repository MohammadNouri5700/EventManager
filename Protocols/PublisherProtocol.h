//
// Created by aziz on 03.08.21.
//

#ifndef EVENT_MANAGER_PUBLISHERPROTOCOL_H
#define EVENT_MANAGER_PUBLISHERRPROTOCOL_H
#include "../W_mqtt/MqttPublisher.h"
#include "Protocol.h"
#include "../GateWay/Connection/ConnectionMqtt.h"
#include "../GateWay/Node/MqttTag.h"


namespace ProtocolS::Mqtt
{
class PublisherProtocol: public ProtocolS::Protocol, public MqTT::MqttPublisher
{
public:
    PublisherProtocol();
    PublisherProtocol(ConnectionMqtt *Conn);
    PublisherProtocol(const stClient &s);
    virtual ~PublisherProtocol();
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

    void Write(Data* data,Tag* tag) override;

};
}


#endif //EVENT_MANAGER_PUBLISHERPROTOCOL_H
