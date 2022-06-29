//
// Created by bong on 22. 6. 28.
//

#include "TcpServer.h"

#include <utility>

namespace net{

    TcpServer TcpServer::getAddress(InetAddress& address) {
        address_ = address;

        return *this;
    }

    TcpServer TcpServer::getName(std::string name) {
        name_ = std::move(name);

        return *this;
    }

    TcpServer TcpServer::getEventMgr() {
        return *this;
    }

    TcpServer TcpServer::getIoEventNum() {
        return *this;
    }

    void TcpServer::start() {
        if(!address_.isUnspecified()){
            return;
        }


    }
}