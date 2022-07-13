//
// Created by bong on 22. 7. 13.
//

#ifndef MYSERVERFW_ACCEPTOR_H
#define MYSERVERFW_ACCEPTOR_H


#include "EventLoop.h"

class Acceptor {
public:
    explicit Acceptor(EventLoop* loop);

    void listen();

};


#endif //MYSERVERFW_ACCEPTOR_H
