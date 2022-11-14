//
// Created by aziz on 27.11.21.
//

#include "PiPe.h"

const size_t Read_szie = 1024;

PiPe::PiPe(std::string Name  ):pipeName{Name}
{

    mkfifo(pipeName.c_str(), 0666);
}

PiPe::~PiPe()
{
    close(fd);
    //unlink(pipeName.c_str());
}


std::string PiPe_read::Read(void)
{
    char c[1024];
    ssize_t size = read(fd, c, 1024);
    if (size == -1) {
        return "";
    }
    return std::string{c};
}

PiPe_read::PiPe_read(std::string Name  ): PiPe{Name}
{
    fd = open(pipeName.c_str(), O_CREAT | O_RDONLY, 0600);
    if (fd < 0) {
        std::cerr << "err in create or open pipe file";
    }
}

void PiPe_write::Write(std::string str)
{
    ssize_t size =write(fd, str.c_str(), str.size()+1);
    if (size == -1) {
        exit(0);
    }
}

PiPe_write::PiPe_write(std::string Name  ): PiPe{Name}
{
    fd = open(pipeName.c_str(), O_CREAT | O_WRONLY, 0600);
    if (fd < 0) {
        std::cerr << "err in create or open pipe file";
    }
}
