//
// Created by aziz on 04.08.21.
//

#include "EventManager.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <mutex>
#include "Data.h"
#include "../GateWay/Node/NodeList.h"

#include "../Entity/command/command.h"


#define MAX_QUEUE_SIZE 300
extern bool connected;

#include "atomic_queue/atomic_queue.h"

using Queue = atomic_queue::AtomicQueueB2<Event>; // Use heap-allocated buffer.
Queue EventList = Queue(MAX_QUEUE_SIZE);

extern ProtocolS::NodeList nodeList;

std::mutex end_mutex;

GateWay::EVENT::MANAGER::EventManager::EventManager() {}

GateWay::EVENT::MANAGER::EventManager::~EventManager()
{

}
void GateWay::EVENT::MANAGER::EventManager::Act()
{
    Event begin_e{new ProtocolData{"begin " + std::to_string(NumQueue + 1), nullptr,"que"}};
    EventList.push(std::move(begin_e));
    std::cout<< "\nmanager\n............" << std::endl;
    std::cout<< "\n........... all event............" << std::endl;
    ///.............................................................................................
    std::cout << "size : " << nodeList.size() << std::endl;
    for (auto node : nodeList) {
        auto tags = node;
        for (auto tag : tags.second) {
            if (tag->Timer.Value > 0) {
                std::cout << tag->strGetName() << " : " << tag->Timer.Value << std::endl;
                AddTimer(tag);
            }
        }
    }
}

void GateWay::EVENT::MANAGER::EventManager::AddTimer(ProtocolS::Tag *tag)
{
    auto Timer =[](ProtocolS::Tag *tag) {

        (void)tag; //TODO
        /*  Event e{new TagData{tag}, {TYPE::TIMER,"TIMER" }, {TYPE::UPDATE,tag->strGetName()}};
          EventList.push_back(std::move(e));*/
    };
}

// void GateWay::EVENT::MANAGER::EventManager::addEvent(Event e)
// {
//     EventList.push_back(std::move(e));
// }



