//
// Created by bong on 22. 6. 29.
//

#ifndef MYSERVERFW_EPOLLPOLLER_H
#define MYSERVERFW_EPOLLPOLLER_H

#include <map>
#include <sys/epoll.h>
#include "Poller.h"

class EpollPoller : public Poller {
public:
    EpollPoller();
    ~EpollPoller() override = default;

    void poll(int timeout_ms, std::vector<Channel *> channelList) override;

    void updateChannel(Channel *channel) override;

    void deleteChannel(Channel *channel) override;

private:
    static const int kInitEventListSize = 16;
    int epollfd_;
    std::vector< epoll_event> events_;
    std::map<int, Channel *> channels_;
};


#endif //MYSERVERFW_EPOLLPOLLER_H
