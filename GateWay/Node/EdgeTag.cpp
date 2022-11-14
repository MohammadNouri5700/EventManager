//
// Created by aziz on 19.12.21.
//

#include "EdgeTag.h"
#include "../../Entity/EdgeProcess/edgeprocess.h"

#include "../Event.h"
#include "NodeList.h"
#include "atomic_queue/atomic_queue.h"

using Queue = atomic_queue::AtomicQueueB2<Event>; // Use heap-allocated buffer.
extern Queue EventList;

void ProtocolS::EdgeTag::setValue(void *value, size_t Size)
{
    Tag::setValue(value, Size);
}

void ProtocolS::EdgeTag::setSubject(ProtocolS::Protocol *subject)
{
    Tag::setSubject(subject);
}

void ProtocolS::EdgeTag::SendEvent()
{

}

void ProtocolS::EdgeTag::UpdateValue()
{
    Tag::UpdateValue();
    edgesProcessEntity edge{edgesEntity{12, Name.Value, strFunc_.Value}};
    for (auto t:ptrTags_) {
        try {
            edge.tagsEntity_.emplace_back(15, t->Name.Value, 15/*t->ValueType.Value*/, t->SizeValue, 15, t->read, t->write, t->Value);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }

    }
    std::string  str{to_string(edge.toJson())};
    Event e{new ProtocolData{str, nullptr,Name.Value}, TYPE::SEND};
    EventList.push(std::move(e));

}

void ProtocolS::EdgeTag::Print()
{
    Tag::Print();
}

ProtocolS::EdgeTag::~EdgeTag()
{

}

int ProtocolS::EdgeTag::GetType()
{
    return Tag::GetType();
}

void ProtocolS::EdgeTag::addTag(Tag *tag)
{
    ptrTags_.push_back(tag);
}

ProtocolS::EdgeTag::EdgeTag(xmlEdge * nEdge): Tag(nEdge)
{

    strFunc_ = nEdge->Func;

    for (auto name: nEdge->tags) {
        auto t = findTag(name.Value);
        if (t!= nullptr)
            ptrTags_.push_back(t);
    }

}


