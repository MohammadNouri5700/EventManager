//
// Created by aziz on 19.12.21.
//

#ifndef EVENT_MANAGER_EDGETAG_H
#define EVENT_MANAGER_EDGETAG_H

#include "Tag.h"
#include "../Connection/ConnectionEdge.h"

namespace ProtocolS
{
class EdgeTag : public Tag
{
private:
    strTag strFunc_{};
    std::vector<Tag*> ptrTags_{};
public:
    EdgeTag(xmlEdge * nEdge);

    void setValue(void *value, size_t Size) override;

    void setSubject(Protocol *subject) override;

    void SendEvent() override;

    void UpdateValue() override;

    void Print() override;

    ~EdgeTag() override;

    int GetType() override;
    void addTag(Tag *tag);
};
}


#endif //EVENT_MANAGER_EDGETAG_H
