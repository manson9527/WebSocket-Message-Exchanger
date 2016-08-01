cmake_minimum_required(VERSION 3.5)
project(WebSocket_Message_Exchanger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/main.cpp)

add_executable(WebSocket_Message_Exchanger ${SOURCE_FILES})