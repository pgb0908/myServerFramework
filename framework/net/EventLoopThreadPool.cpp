//
// Created by bong on 22. 7. 13.
//

#include "EventLoopThreadPool.h"


void EventLoopThreadPool::start() {
    for (unsigned int i = 0; i < loopThreadVector_.size(); ++i)
    {
        loopThreadVector_[i]->run();
    }
}

EventLoopThreadPool::EventLoopThreadPool(int thread_num, const std::string &name): loopIndex_(0) {
    for (size_t i = 0; i < thread_num; ++i)
    {
        loopThreadVector_.emplace_back(std::make_shared<EventLoopThread>(name));
    }
}

std::vector<EventLoop *> EventLoopThreadPool::getLoops() const {
    std::vector<EventLoop *> ret;
    for (auto &loopThread : loopThreadVector_)
    {
        ret.push_back(loopThread->getLoop());
    }
    return ret;
}

void EventLoopThreadPool::wait() {
    for (unsigned int i = 0; i < loopThreadVector_.size(); ++i)
    {
        loopThreadVector_[i]->wait();
    }
}

EventLoop *EventLoopThreadPool::getNextLoop() {
    if (!loopThreadVector_.empty())
    {
        EventLoop *loop = loopThreadVector_[loopIndex_]->getLoop();
        ++loopIndex_;
        if (loopIndex_ >= loopThreadVector_.size())
            loopIndex_ = 0;
        return loop;
    }
    return nullptr;
}

EventLoop *EventLoopThreadPool::getLoop(size_t id) {
    if (id < loopThreadVector_.size())
        return loopThreadVector_[id]->getLoop();
    return nullptr;
}
