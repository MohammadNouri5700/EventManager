//
// Created by aziz on 27.11.21.
//

#ifndef IPC_PIPE_H
#define IPC_PIPE_H

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <cstdlib>
#include <cstdio>



#include <string>
#include <iostream>

class PiPe
{
public:
    PiPe(std::string pipeName = "fifo");
    virtual ~PiPe();

protected:
    int fd{};
    std::string pipeName{};
};

class PiPe_read : public PiPe
{
public:
    PiPe_read(std::string Name);

    std::string Read(void);
};

class PiPe_write : public PiPe
{
public:
    void Write(std::string);

    PiPe_write(std::string Name);
};
#endif //IPC_PIPE_H
