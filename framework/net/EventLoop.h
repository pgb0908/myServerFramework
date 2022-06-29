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

class EventLoop {
public:

    EventLoop();
    ~EventLoop();

    /**
     * @brief Run the event loop. This method will be blocked until the event
     * loop exits.
     *
     */
    void loop();

    /**
     * @brief Let the event loop quit.
     *
     */
    void quit();


    /**
     * @brief Return true if the current thread is the thread to which the event
     * loop belongs.
     *
     * @return true
     * @return false
     */
    bool isInLoopThread() const {
        return threadId_ == std::this_thread::get_id();
    };

    /**
     * @brief Get the event loop of the current thread. Return nullptr if there
     * is no event loop in the current thread.
     *
     * @return EventLoop*
     */
    static EventLoop *getEventLoopOfCurrentThread();

    /**
     * @brief Run the function f in the thread of the event loop.
     *
     * @param f
     * @note If the current thread is the thread of the event loop, the function
     * f is executed directly before the method exiting.
     */
    template<typename Functor>
    inline void runInLoop(Functor &&f) {
        if (isInLoopThread()) {
            f();
        } else {
            queueInLoop(std::forward<Functor>(f));
        }
    }

    /**
     * @brief Run the function f in the thread of the event loop.
     *
     * @param f
     * @note The difference between this method and the runInLoop() method is
     * that the function f is executed after the method exiting no matter if the
     * current thread is the thread of the event loop.
     */
    void queueInLoop(const std::function<void()> &f);

    void queueInLoop(std::function<void()> &&f);


    /**
     * @brief Move the EventLoop to the current thread, this method must be
     * called before the loop is running.
     *
     */
    void moveToCurrentThread();

    /**
     * @brief Update channel status. This method is usually used internally.
     *
     * @param chl
     */
    void updateChannel(Channel *chl);

    /**
     * @brief Remove a channel from the event loop. This method is usually used
     * internally.
     *
     * @param chl
     */
    void removeChannel(Channel *chl);



    /**
     * @brief Return true if the event loop is running.
     *
     * @return true
     * @return false
     */
    bool isRunning() {
        return looping_.load(std::memory_order_acquire) &&
               (!quit_.load(std::memory_order_acquire));
    }



private:

    void wakeup();

    void wakeupRead();

    std::atomic<bool> looping_;
    std::thread::id threadId_;
    std::atomic<bool> quit_;
    std::unique_ptr<Poller> poller_;

    //std::vector<Channel *> activeChannels_;
    Channel *currentActiveChannel_;

    //MpscQueue <std::function<void()>> funcs_;
    //std::unique_ptr <TimerQueue> timerQueue_;
    //MpscQueue <std::function<void()>> funcsOnQuit_;
    //bool callingFuncs_{false};
    //int wakeupFd_;
    std::unique_ptr<Channel> wakeupChannelPtr_;


    //size_t index_{std::numeric_limits<size_t>::max()};
    //EventLoop **threadLocalLoopPtr_;
};


#endif //MYSERVERFW_EVENTLOOP_H
