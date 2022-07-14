//
// Created by bong on 22. 6. 29.
//

#include <iostream>
#include "EventLoop.h"
#include "Channel.h"
#include "poll/EpollPoller.h"


void EventLoop::queueInLoop(const std::function<void()> &f) {

}

void EventLoop::queueInLoop(std::function<void()> &&f) {

}

EventLoop *EventLoop::getEventLoopOfCurrentThread() {
    return nullptr;
}

EventLoop::EventLoop() : looping_(false),
                         threadId_(std::this_thread::get_id()),
                         quit_(false),
                         poller_(new EpollPoller) {


}

EventLoop::~EventLoop() {

}

void EventLoop::moveToCurrentThread() {

}

void EventLoop::updateChannel(Channel *chl) {

}

void EventLoop::removeChannel(Channel *chl) {

}

void EventLoop::abortNotInLoopThread() {
    std::cout << "It is forbidden to run loop on threads other than main-loop thread";
    exit(1);
}
