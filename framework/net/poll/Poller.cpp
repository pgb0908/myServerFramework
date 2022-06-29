//
// Created by bong on 22. 6. 29.
//

#include "Poller.h"
#include "EpollPoller.h"

Poller* Poller::newPoller() {
    return new EpollPoller();
}
