//
// Created by bong on 22. 7. 13.
//

#ifndef MYSERVERFW_EVENTLOOPTHREADPOOL_H
#define MYSERVERFW_EVENTLOOPTHREADPOOL_H

#include <string>
#include <memory>
#include <vector>
#include "EventLoopThread.h"

class EventLoopThreadPool {
public:
    explicit EventLoopThreadPool(int thread_num, const std::string &name = "EventLoopThreadPool");
    void start();
    void wait();
    size_t size()
    {
        return loopThreadVector_.size();
    }

    EventLoop *getNextLoop();
    EventLoop *getLoop(size_t id);
    std::vector<EventLoop *> getLoops() const;

private:
    std::vector<std::shared_ptr<EventLoopThread>> loopThreadVector_;
    size_t loopIndex_;

};


#endif //MYSERVERFW_EVENTLOOPTHREADPOOL_H
