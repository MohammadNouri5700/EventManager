
//
// Created by aziz on 15.10.21.
//

#ifndef EVENT_MANAGER_COAPTAG_H
#define EVENT_MANAGER_COAPTAG_H

#include "Tag.h"
#include "../Connection/ConnectionCoap.h"
namespace ProtocolS
{

class CoapTag: public Tag
{
public:
    strTag URI;
    strTag Token;
    strTag Request;
public:
    CoapTag(xmlCoap *node);

    void setValue(void *value, size_t Size) override;

    void setSubject(Protocol *subject) override;

    void SendEvent() override;

    void Print() override;

    void UpdateValue() override;

    ~CoapTag() override;

    int GetType() override;
};

}
#endif //EVENT_MANAGER_COAPTAG_H
