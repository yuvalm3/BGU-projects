cmake_minimum_required(VERSION 3.29)
project(C__)

set(CMAKE_CXX_STANDARD 11)

add_executable(C__ main.cpp
        Entity.cpp
        Entity.h
        Room.h
        Room.cpp
        Game.h
        Game.cpp)
