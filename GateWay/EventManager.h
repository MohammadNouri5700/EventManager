//
// Created by aziz on 04.08.21.
//

#ifndef EVENT_MANAGER_EVENTMANAGER_H
#define EVENT_MANAGER_EVENTMANAGER_H
#include <list>
#include <deque>
#include <string>
#include <functional>
#include <iterator>
#include <utility>
#include <boost/asio.hpp>
#include <chrono>

#include "SignalS.h"
#include "ThreadPool.h"
#include "Thread_Call.h"
#include "Node/Tag.h"




class Event;

#include "atomic_queue/atomic_queue.h"

using Queue = atomic_queue::AtomicQueueB2<Event>; // Use heap-allocated buffer.
extern Queue EventList;

namespace GateWay::EVENT::MANAGER
{
using EventCallbackType = std::function<bool(Data&)>;
class EventManager
{
public:
    EventManager();

    virtual ~EventManager();
    void Act();
    void AddTimer(ProtocolS::Tag *tag);
    void addEvent(Event e);

    void AddMerge(Event event);

private:
    ItreatorType Begin{};
    size_t NumQueue{0};
    Thread_Call TimerEvent{};
};
}



#endif //EVENT_MANAGER_EVENTMANAGER_H
