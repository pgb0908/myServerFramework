//
// Created by bong on 22. 6. 29.
//

#include "EpollPoller.h"
#include <unistd.h>

void EpollPoller::poll(int timeout_ms, std::vector<Channel *>* channelList) {

}

void EpollPoller::updateChannel(Channel *channel) {

}

void EpollPoller::deleteChannel(Channel *channel) {

}

EpollPoller::EpollPoller() {
    epollfd_ = ::epoll_create1(EPOLL_CLOEXEC);
    events_.reserve(kInitEventListSize);

}
