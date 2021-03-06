//
// Created by bong on 22. 6. 28.
//

#include "TcpServer.h"
#include <iostream>

#include <utility>


TcpServer &TcpServer::Address(InetAddress &address) {
    address_ = address;

    return *this;
}

TcpServer &TcpServer::Name(std::string name) {
    name_ = name;

    return *this;
}

TcpServer &TcpServer::MainLoop(EventLoop* loop) {
    mainLoop_ = loop;
    return *this;
}

TcpServer &TcpServer::IoEventNum(int io_nums) {
    if (io_nums < 0) {
        io_num_ = 0;
    } else {
        io_num_ = io_nums;
    }

    loopPoolPtr_ = std::make_shared<EventLoopThreadPool>(io_num_);
    loopPoolPtr_->start();

    return *this;
}

void TcpServer::start() {
    if (address_.isUnspecified()) {
        std::cout << "server address is not set" << std::endl;
        return;
    }
    if (mainLoop_ == nullptr) {
        std::cout << "mainThread is not set" << std::endl;
        return;
    }

    bool reUseAddr = true;
    bool reUsePort = true;

    acceptorPtr_ = std::unique_ptr<Acceptor>(new Acceptor(mainLoop_,address_,
                                                                  reUseAddr, reUsePort));
    std::cout << "tcp server : acceptor is made" << std::endl;

    mainLoop_->runInLoop(
            [this]() -> void {
                std::cout << "tcp server :  run in loop" << std::endl;

                started_ = true;

                // ioLoop 동작 정의
                for (int i = 0; i < io_num_; i++) {}

                // acceptor listen 준비
                acceptorPtr_->listen();
            });

}

TcpServer::TcpServer() : mainLoop_(nullptr), io_num_(0) {

}
