//
// Created by aziz on 24.11.21.
//

#ifndef UNTITLED3_MOUSE_H
#define UNTITLED3_MOUSE_H
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
struct input_event;
class mouse
{
public:
    void loop();
    mouse();
    virtual ~mouse(){}

private:
    int fd = 0;
    int i = 0;
    input_event ev[64];
    bool l = 0;
    bool r = 0;
    int x =0;
    int y=0;
    int roll=0;
};
#endif //UNTITLED3_MOUSE_H
