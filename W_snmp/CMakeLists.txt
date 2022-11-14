cmake_minimum_required(VERSION 3.18)
project(W_snmp)

set(CMAKE_CXX_STANDARD 20)
add_library(W_snmp SnmpAgent.cpp SnmpAgent.h)