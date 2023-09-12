//
// Created by user on 7/25/23.
//
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include "Connection.h"


#define PORT 8080

#ifndef EVENT_MANAGER_CONNECTIONTCP_H
#define EVENT_MANAGER_CONNECTIONTCP_H


class ConnectionTcp {

    std::thread* thread;

public:
    void async_run (int interval_sec);
    ~ConnectionTcp();
    ConnectionTcp();
    void startServer(int interval_sec);


};


#endif //EVENT_MANAGER_CONNECTIONTCP_H
