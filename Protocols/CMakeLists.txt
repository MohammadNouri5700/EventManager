cmake_minimum_required(VERSION 3.18)
project(Protocols)

set(CMAKE_CXX_STANDARD 17)
add_library(Protocols
        SubscriberProtocol.cpp SubscriberProtocol.h
        Protocol.cpp Protocol.h
        ServerProtocol.cpp ServerProtocol.h
        MasterProtocol.cpp MasterProtocol.h
        ServerProtocol.cpp ServerProtocol.h
        S7Protocol.cpp S7Protocol.h
        PublisherProtocol.cpp PublisherProtocol.h
        )