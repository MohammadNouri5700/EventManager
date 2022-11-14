cmake_minimum_required(VERSION 3.16.5)
project(ErrorManager)

set(CMAKE_CXX_STANDARD 20)

add_library(ErrorManager ErrorManager.cpp ErrorManager.h Error.cpp Error.h)
