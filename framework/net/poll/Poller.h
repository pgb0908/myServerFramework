//
// Created by bong on 22. 6. 29.
//

#ifndef MYSERVERFW_POLLER_H
#define MYSERVERFW_POLLER_H

#include "../EventLoop.h"


class Channel;

class Poller {

public:
    Poller() = default;
    virtual ~Poller() = default;

    static Poller *newPoller();

    virtual void poll(int timeout_ms, std::vector<Channel *> channelList) = 0;
    virtual void updateChannel(Channel *channel) = 0;
    virtual void deleteChannel(Channel *channel) = 0;
};


#endif //MYSERVERFW_POLLER_H
