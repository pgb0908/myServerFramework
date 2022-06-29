//
// Created by bong on 22. 6. 28.
//

#include "TcpServer.h"
#include <iostream>

#include <utility>



    TcpServer& TcpServer::Address(InetAddress& address) {
        this->address_ = address;

        return *this;
    }

    TcpServer& TcpServer::Name(std::string name) {
        this->name_ = name;

        return *this;
    }

    TcpServer& TcpServer::MainLoop(std::shared_ptr<EventLoop> loop) {
        this->mainLoop_ = std::move(loop);
        return *this;
    }

    TcpServer& TcpServer::IoEventNum(int io_nums) {
        this->io_num_ = io_nums;
        return *this;
    }

    void TcpServer::start() {
        if(io_num_ == 0){
            io_num_ = 1;
        }
        if(!address_.isUnspecified()){
            std::cout << "server address is not set" << std::endl;
            return;
        }
        if(mainLoop_ == nullptr){
            std::cout << "mainThread is not set" << std::endl;
            return;
        }


    }

TcpServer::TcpServer():mainLoop_(nullptr),io_num_(0) {

}
