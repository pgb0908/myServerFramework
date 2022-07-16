//
// Created by bong on 22. 6. 29.
//

#include <iostream>
#include "EventLoop.h"
#include "Channel.h"
#include "poll/EpollPoller.h"
#include <sys/eventfd.h>
#include <cassert>
#include <unistd.h>

const int kPollTimeMs = 10000;

int createEventfd()
{
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0)
    {
        std::cout << "Failed in eventfd" << std::endl;
        abort();
    }

    return evtfd;
}

thread_local EventLoop *t_loopInThisThread = nullptr;

EventLoop::EventLoop() : looping_(false),
                         threadId_(std::this_thread::get_id()),
                         quit_(false),
                         poller_(new EpollPoller(this)),
                         currentActiveChannel_(nullptr),
                         eventHandling_(false),
                         wakeupFd_(createEventfd()),
                         wakeupChannelPtr_(new Channel(this, wakeupFd_)),
                         threadLocalLoopPtr_(&t_loopInThisThread)
{

    if(t_loopInThisThread){

        std::cout << "There is already an EventLoop in this thread";
        exit(-1);
    }

    t_loopInThisThread = this;

    wakeupChannelPtr_->setReadCallback(std::bind(&EventLoop::wakeupRead, this));
    wakeupChannelPtr_->enableReading();

}

void EventLoop::queueInLoop(const std::function<void()> &f) {

}

void EventLoop::queueInLoop(Func &&func) {
    funcs_.enqueue(func);
    if (!isInLoopThread() || !looping_.load(std::memory_order_acquire))
    {
        wakeup();
    }
}

EventLoop *EventLoop::getEventLoopOfCurrentThread() {
    return nullptr;
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

void EventLoop::loop() {
    assert(!looping_);
    assertInLoopThread();
    looping_.store(true, std::memory_order_release);
    quit_.store(false, std::memory_order_release);

    while(!quit_.load(std::memory_order_acquire)){
        activeChannels_.clear();
        poller_->poll(kPollTimeMs, &activeChannels_);

        eventHandling_ = true;
        for (auto & activeChannel : activeChannels_)
        {
            currentActiveChannel_ = activeChannel;
            currentActiveChannel_->handleEvent();
        }
        currentActiveChannel_ = nullptr;
        eventHandling_ = false;
        // std::cout << "looping" << endl;
        doRunInLoopFuncs();
    }
    looping_.store(false, std::memory_order_release);

    Func f;
    while (funcsOnQuit_.dequeue(f))
    {
        f();
    }

}

void EventLoop::quit() {
    quit_.store(true, std::memory_order_release);

    if (!isInLoopThread())
    {
        wakeup();
    }
}

void EventLoop::wakeup() const {
    uint64_t tmp = 1;
    int ret = write(wakeupFd_, &tmp, sizeof(tmp));
    (void)ret;
}

void EventLoop::doRunInLoopFuncs() {
    callingFuncs_ = true;
    {
        // the destructor for the Func may itself insert a new entry into the
        // queue
        while (!funcs_.empty())
        {
            Func func;
            while (funcs_.dequeue(func))
            {
                func();
            }
        }
    }
    callingFuncs_ = false;
}

void EventLoop::wakeupRead() {
    ssize_t ret = 0;

    uint64_t tmp;
    ret = read(wakeupFd_, &tmp, sizeof(tmp));

    if (ret < 0){
        std::cout << "wakeup read error" << std::endl;
    }
}
