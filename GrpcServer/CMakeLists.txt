cmake_minimum_required(VERSION 3.5.1)

project(GrpcServer C CXX)
set(CMAKE_CXX_STANDARD 17)


add_library(${PROJECT_NAME} grpcserver.cpp mqttservice.cpp wifiservice.cpp modbusservice.cpp s7service.cpp 
                    convertservice.cpp mqttpodservice.cpp nodeservice.cpp serialservice.cpp networkservice.cpp
                    startupservice.cpp gpsservice.cpp )

target_link_libraries(${PROJECT_NAME} protos mosquittopp)

target_include_directories(GrpcServer PUBLIC ./)

target_include_directories(GrpcServer PUBLIC ../ConnectionManager)
