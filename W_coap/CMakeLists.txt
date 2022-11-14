cmake_minimum_required(VERSION 3.16.5)
project(W_coap)

set(CMAKE_CXX_STANDARD 17)
add_library(W_coap
            Coap.cpp Coap.h
            Resource.cpp Resource.h
            Context.cpp Context.h
            Pdu.cpp Pdu.h
            Sessions.cpp Sessions.h
            Server.cpp Server.h
            client.cpp client.h
            EndPoint.cpp EndPoint.h
            CoapNode.cpp CoapNode.h)


