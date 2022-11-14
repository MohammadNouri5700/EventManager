cmake_minimum_required(VERSION 3.16.5)
project(W_s7)

set(CMAKE_CXX_STANDARD 20)
add_library(W_S7 SNAP7_Client.cpp S7Client.cpp)