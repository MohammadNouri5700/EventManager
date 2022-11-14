//
// Created by aziz on 28.11.21.
//

#include "key.h"
#include "../GateWay/Event.h"
#include "eventfinder.h"
#include "atomic_queue/atomic_queue.h"

using Queue = atomic_queue::AtomicQueueB2<Event>; // Use heap-allocated buffer.
extern Queue EventList;

key::key()
{
    auto res = find_event("keyboard");
    if ((fd = open(res.c_str(), O_RDONLY)) == -1) {
        perror("opening device");
        exit(EXIT_FAILURE);
    }
}

void key::loop()
{
    bool key;
    while (read(fd, &ie, sizeof(struct input_event))) {
        if (ie.code == 0 || ie.value>3)
            continue;
        key = true;
        if (ie.code == 42 || ie.code == 54) {
            shift_state = ie.value;
            key = false;
        }
        if (ie.code == 56 || ie.code == 100) {
            alt_state = ie.value;
            key = false;
        }
        if (ie.code == 29 || ie.code == 97) {
            ctrl_state = ie.value;
            key = false;
        }

        std::string str;
        str = "{\"messageId\":\"messageKey\",\"messageKey\":{\"s\":\""
              + std::to_string(shift_state) + "\",\"c\":\""
              + std::to_string(ctrl_state) + "\",\"a\":\""
              + std::to_string(alt_state) + "\",\"k\":\""
              + (key ? Key_list.at(ie.code):"") + "\",\"t\":\""
              + std::to_string(ie.value) +"\"}}";
        /*Event e{new ProtocolData{str}, {TYPE::SEND,"" }, {TYPE::SEND,""}};
        EventList.push_back(std::move(e));*/

    }
}
