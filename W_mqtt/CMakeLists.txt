cmake_minimum_required(VERSION 3.16.5)
project(W_mqtt)

set(CMAKE_CXX_STANDARD 20)
add_library(W_mqtt Mqtt.cpp Mqtt.h MqttSubscriber.cpp MqttSubscriber.h MqttPublisher.cpp MqttPublisher.h NewPublisher.cpp NewPublisher.h)


