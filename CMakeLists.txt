cmake_minimum_required(VERSION 2.8)
project(WebSocket_Message_Exchanger)

include(CMakeDependentOption)

# build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# include files
set(INCLUDE_FILES
        ${SRC}
        ${LIBS}/boost
        ${LIBS}/rapidjson/include
        ${LIBS}/websocketpp
        )

set(LINK_LIBRARY_PATH
        ${LIBS}/boost/stage/lib
        )

# static library files
set(STATIC_LIBRARY_PATH ${LIBS}/boost/stage/lib)
set(STATIC_LIBRARY_FILES
        ${STATIC_LIBRARY_PATH}/libboost_log.a
        ${STATIC_LIBRARY_PATH}/libboost_thread.a
        ${STATIC_LIBRARY_PATH}/libboost_system.a
        )

# source files
set(SOURCE_FILES
        ${SRC}/main.cpp
        )

include_directories(${INCLUDE_FILES})

add_executable(WebSocket_Message_Exchanger ${SOURCE_FILES})
target_link_libraries(WebSocket_Message_Exchanger ${STATIC_LIBRARY_FILES})
