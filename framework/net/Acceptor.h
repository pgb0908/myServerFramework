//
// Created by bong on 22. 7. 13.
//

#ifndef MYSERVERFW_ACCEPTOR_H
#define MYSERVERFW_ACCEPTOR_H


#include "EventLoop.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Socket.h"

class Acceptor {

public:
    explicit Acceptor(EventLoop *loop, InetAddress address, bool reUseAddr, bool reUsePort);

    void listen();

private:
    InetAddress addr_;
    EventLoop* loop_;
    Channel acceptChannel_;
    Socket sock_;

};


#endif //MYSERVERFW_ACCEPTOR_H
