//
// Created by bong on 22. 6. 29.
//

#ifndef MYSERVERFW_EVENTLOOP_H
#define MYSERVERFW_EVENTLOOP_H

#include <thread>
#include <atomic>
#include <vector>
#include <functional>


class Channel;
class Poller;

using Func = std::function<void()>;

class EventLoop {
public:

    EventLoop();
    ~EventLoop();

    void abortNotInLoopThread();

    void assertInLoopThread()
    {
        if (!isInLoopThread())
        {
            abortNotInLoopThread();
        }
    };

    void loop();
    void quit();

    bool isInLoopThread() const {
        return threadId_ == std::this_thread::get_id();
    };

    static EventLoop *getEventLoopOfCurrentThread();

    template<typename Functor>
    inline void runInLoop(Functor &&f) {
        if (isInLoopThread()) {
            f();
        } else {
            queueInLoop(std::forward<Functor>(f));
        }
    }

    void queueInLoop(const std::function<void()> &f);
    void queueInLoop(Func &&f);

    void moveToCurrentThread();

    void updateChannel(Channel *chl);
    void removeChannel(Channel *chl);

    bool isRunning() {
        return looping_.load(std::memory_order_acquire) &&
               (!quit_.load(std::memory_order_acquire));
    }


private:

    void wakeup() const;

    void wakeupRead();

    std::atomic<bool> looping_;
    std::thread::id threadId_;
    std::atomic<bool> quit_;
    std::unique_ptr<Poller> poller_;

    std::vector<Channel *> activeChannels_;
    Channel *currentActiveChannel_;
    bool eventHandling_;

    //MpscQueue<Func> funcs_;
    //std::unique_ptr <TimerQueue> timerQueue_;
    //MpscQueue <std::function<void()>> funcsOnQuit_;
    //bool callingFuncs_{false};

    int wakeupFd_;
    std::unique_ptr<Channel> wakeupChannelPtr_;


    //size_t index_{std::numeric_limits<size_t>::max()};
    EventLoop **threadLocalLoopPtr_;
};


#endif //MYSERVERFW_EVENTLOOP_H
