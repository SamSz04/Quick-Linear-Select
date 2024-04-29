cmake_minimum_required(VERSION 3.27)
project(Q_Lselect)

set(CMAKE_CXX_STANDARD 17)

add_executable(Q_Lselect main.cpp
        quickselect.h
        linearselect.h
        utils.h)
