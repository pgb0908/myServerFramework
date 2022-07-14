//
// Created by bong on 22. 6. 29.
//

#include <poll.h>
#include <iostream>
#include <cassert>
#include "Channel.h"

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

void Channel::update() {
    loop_->updateChannel(this);
}

void Channel::handleEvent() {
    if (events_ == kNoneEvent)
        return;
    handleEventSafely();
}

void Channel::handleEventSafely() {
    if (eventCallback_)
    {
        eventCallback_();
        return;
    }
    if ((revents_ & POLLHUP) && !(revents_ & POLLIN))
    {
        std::cout << "handle close" << std::endl;
        if (closeCallback_)
            closeCallback_();
    }
    if (revents_ & (POLLNVAL | POLLERR))
    {
        std::cout << "handle error" << std::endl;
        if (errorCallback_)
            errorCallback_();
    }
    if (revents_ & (POLLIN | POLLPRI | POLLRDHUP))
    {
        std::cout << "handle read" << std::endl;
        if (readCallback_)
            readCallback_();
    }
    if (revents_ & POLLOUT)
    {
        std::cout << "handle write" << std::endl;
        if (writeCallback_)
            writeCallback_();
    }
}

Channel::Channel(EventLoop *loop, int fd) :
 loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1), tied_(false)
 {}

void Channel::remove() {
    assert(events_ == kNoneEvent);
    addedToLoop_ = false;
    loop_->removeChannel(this);
}
