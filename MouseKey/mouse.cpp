//
// Created by aziz on 24.11.21.
//

#include "mouse.h"
#include "../GateWay/Event.h"
#include "eventfinder.h"
#include "atomic_queue/atomic_queue.h"

using Queue = atomic_queue::AtomicQueueB2<Event>; // Use heap-allocated buffer.
extern Queue EventList;

void mouse::loop()
{
    std::cout << "loop" ;
    while (true) {
        auto bytes = read(fd, &ev, sizeof(struct input_event) * 64);

        if (bytes > 0) {

            bool L=0, R=0;

            for (i = 0; i < (int) (bytes / sizeof(struct input_event)); i++) {

                if (ev[i].type == EV_KEY) {

                    if (ev[i].code == BTN_LEFT) {
                        L = ev[i].value;
                    }
                    if (ev[i].code == BTN_RIGHT) {
                        R = ev[i].value;
                    }
                }

                if (ev[i].type == EV_REL) {

                    if (ev[i].code == REL_X) {
                        x = ev[i].value;
                    }
                    if (ev[i].code == REL_Y) {
                        y = ev[i].value;
                    }

                    if (ev[i].code == REL_WHEEL) {
                        roll = ev[i].value;
                    }

                }

            }

            if ((x != 0 || y !=  0) || (l != L || r != R)) {
                std::string str{};
                str = "{\"messageId\":\"mouse\",\"messageMouse\":{\"l\":\"";
                str += std::to_string(l) + "\",\"r\":\"";
                str += std::to_string(r) + "\",\"x\":\"";
                str += std::to_string(x) + "\",\"y\":\"";
                str += std::to_string(y) + "\", \"roll\":\"";
                str += std::to_string(roll) + "\"}}";
                /*Event e{new ProtocolData{std::move(str)}, {TYPE::SEND,"" }, {TYPE::SEND,""}};
                EventList.push_back(std::move(e));*/
                x = y = roll = 0;
            }

        }
    }
}

mouse::mouse()
{
    auto res = find_event("mouse");
    if ((fd = open(res.c_str(), O_RDONLY)) == -1) {
        perror("opening device");
        exit(EXIT_FAILURE);
    }
}
