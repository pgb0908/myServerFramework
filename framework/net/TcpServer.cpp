//
// Created by bong on 22. 6. 28.
//

#include "TcpServer.h"

#include <utility>



    TcpServer TcpServer::getAddress(InetAddress& address) {
        address_ = address;

        return *this;
    }

    TcpServer TcpServer::getName(std::string name) {
        name_ = std::move(name);

        return *this;
    }

    TcpServer TcpServer::getMainLoopThread(MainLoopThread& mainLoopThread) {
        mainLoopThread_ = mainLoopThread;
        return *this;
    }

    TcpServer TcpServer::getIoEventNum(int io_nums) {
        io_num_ = io_nums;
        return *this;
    }

    void TcpServer::start() {
        if(!address_.isUnspecified()){
            return;
        }


    }
