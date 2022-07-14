//
// Created by bong on 22. 6. 29.
//

#ifndef MYSERVERFW_EVENTLOOPTHREAD_H
#define MYSERVERFW_EVENTLOOPTHREAD_H

#include <string>
#include <mutex>
#include <future>
#include "EventLoop.h"

class EventLoopThread {
public:
    explicit EventLoopThread(std::string  threadName = "MainLoopThead");
    ~EventLoopThread();

    void run();
    void wait();

    EventLoop* getLoop(){
        return loop_.get();
    }

private:
    std::string threadName_;
    std::shared_ptr<EventLoop> loop_;
    std::promise<std::shared_ptr<EventLoop>> promiseForLoopPointer_;
    std::once_flag once_;
    std::promise<int> promiseForLoop_;
    std::promise<int> promiseForRun_;
    std::thread thread_;

    void loopFunc();
};


#endif //MYSERVERFW_EVENTLOOPTHREAD_H
