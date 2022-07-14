//
// Created by bong on 22. 6. 29.
//

#ifndef MYSERVERFW_MAINLOOPTHREAD_H
#define MYSERVERFW_MAINLOOPTHREAD_H

#include <string>
#include "EventLoop.h"

class MainLoopThread {
public:
    explicit MainLoopThread(std::string  threadName = "MainLoopThead");

    void run();
    void wait();

    EventLoop* getLoop(){
        return loop_;
    }

private:
    std::string threadName_;
    EventLoop* loop_;
};


#endif //MYSERVERFW_MAINLOOPTHREAD_H
