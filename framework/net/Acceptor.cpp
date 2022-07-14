//
// Created by bong on 22. 7. 13.
//

#include "Acceptor.h"

Acceptor::Acceptor(EventLoop *loop, InetAddress address, bool reUseAddr, bool reUsePort)
    : sock_(Socket::createNonblockingSocket(address.getSockAddr()->sa_family)),
      addr_(address),
      loop_(loop),
      acceptChannel_(loop, sock_.getSockFd()){

    if (addr_.toPort() == 0)
    {
        addr_ = InetAddress{Socket::getLocalAddr(sock_.getSockFd())};
    }
}

void Acceptor::listen() {
    loop_->assertInLoopThread();
    sock_.listen();
    acceptChannel_.enableReading();
}
