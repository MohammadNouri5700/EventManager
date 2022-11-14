//
// Created by aziz on 04.12.21.
//

#ifndef EVENT_MANAGER_EVENTHANDLER_H
#define EVENT_MANAGER_EVENTHANDLER_H
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
namespace GateWay::EVENT::HANDLER
{
class EventHandler
{
public:
    EventHandler();
    virtual ~EventHandler();
    void Act();

private:
    ThreadPool PoolQueue{4, 10};
    ThreadPool PoolEvent{10, 50};
    Thread_Call Caller{};
};
}


#endif //EVENT_MANAGER_EVENTHANDLER_H
