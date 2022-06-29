//
// Created by bong on 22. 6. 29.
//

#include "EventLoop.h"
#include "poll/Poller.h"
#include "Channel.h"


void EventLoop::queueInLoop(const std::function<void()> &f) {

}

void EventLoop::queueInLoop(std::function<void()> &&f) {

}

EventLoop *EventLoop::getEventLoopOfCurrentThread() {
    return nullptr;
}

EventLoop::EventLoop() :   looping_(false),
                                threadId_(std::thread::id()),
                                quit_(false),
                               poller_(Poller::newPoller())
{


}

EventLoop::~EventLoop() {

}

void EventLoop::moveToCurrentThread() {

}

void EventLoop::updateChannel(Channel *chl) {

}

void EventLoop::removeChannel(Channel *chl) {

}
