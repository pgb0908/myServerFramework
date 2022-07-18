//
// Created by bong on 22. 6. 29.
//

#ifndef MYSERVERFW_EPOLLPOLLER_H
#define MYSERVERFW_EPOLLPOLLER_H

#include <map>
#include <sys/epoll.h>
#include "Poller.h"
#include "../EventLoop.h"

using EventList = std::vector<struct epoll_event>;

class EpollPoller : public Poller {
public:
    explicit EpollPoller(EventLoop *loop);
    ~EpollPoller() override;

    void poll(int timeout_ms, std::vector<Channel *>* channelList) override;

    void updateChannel(Channel *channel) override;

    void removeChannel(Channel *channel) override;

private:
    static const int kInitEventListSize = 16;
    int epollfd_;
    EventList events_;
    void update(int operation, Channel *channel);
    using ChannelMap = std::map<int, Channel *>;
    ChannelMap channels_;
    void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;
};


#endif //MYSERVERFW_EPOLLPOLLER_H
