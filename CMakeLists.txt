cmake_minimum_required(VERSION 3.5)
project(myServerFW)

set(myServerFW_MAJOR_VERSION 1)
set(myServerFW_MINOR_VERSION 0)
set(myServerFW_PATCH_VERSION 0)
set(myServerFW_VERSION
        ${myServerFW_MAJOR_VERSION}.${myServerFW_MINOR_VERSION}.${myServerFW_PATCH_VERSION})

message(STATUS "myServerFW VERSION : ${myServerFW_VERSION}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


## project shard lib 생성
add_library(${PROJECT_NAME} SHARED)
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${myServerFW_VERSION}
        SOVERSION ${myServerFW_MAJOR_VERSION})


## project 링킹할 것들

## project 소스코드
set(PROJECT_SOURCES
        framework/net/TcpServer.cpp
        framework/net/InetAddress.cpp
        framework/net/MainLoopThread.cpp
        framework/net/EventLoop.cpp
        framework/net/poll/Poller.cpp
        framework/net/poll/EpollPoller.cpp
        framework/net/Channel.cpp
        framework/net/EventLoopThreadPool.cpp
        framework/net/Acceptor.cpp
        framework/net/Socket.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
        ${PROJECT_SOURCES})


add_subdirectory(example)