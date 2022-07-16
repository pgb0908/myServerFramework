//
// Created by bong on 22. 6. 29.
//

#ifndef MYSERVERFW_POLLER_H
#define MYSERVERFW_POLLER_H

#include "../EventLoop.h"


class Channel;

class Poller {

public:
    explicit Poller(EventLoop *loop):ownerLoop_(loop){};
    virtual ~Poller() = default;


    void assertInLoopThread()
    {
        ownerLoop_->assertInLoopThread();
    }

    virtual void poll(int timeout_ms, std::vector<Channel *>* channelList) = 0;
    virtual void updateChannel(Channel *channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;
private:
    EventLoop *ownerLoop_;
};


#endif //MYSERVERFW_POLLER_H
