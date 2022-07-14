//
// Created by bong on 22. 6. 29.
//

#include "EventLoopThread.h"
#include <utility>

#include <sys/prctl.h>

EventLoopThread::EventLoopThread(std::string threadName):
                        threadName_(std::move(threadName)),
                        thread_([this](){ loopFunc(); })
{
    auto loop_f = promiseForLoopPointer_.get_future();
    loop_ = loop_f.get();
}

EventLoopThread::~EventLoopThread() {
    if (thread_.joinable())
    {
        thread_.join();
    }
}

void EventLoopThread::run() {
/*    std::call_once(once_, [this]() {
        auto f = promiseForLoop_.get_future();
        promiseForRun_.set_value(1);
        // Make sure the event loop loops before returning.
        (void)f.get();
    });*/

}

void EventLoopThread::wait() {
    thread_.join();
}

void EventLoopThread::loopFunc() {
    ::prctl(PR_SET_NAME, threadName_.c_str());

    thread_local static std::shared_ptr<EventLoop> loop =
            std::make_shared<EventLoop>();
    promiseForLoopPointer_.set_value(loop);

    loop->loop();
}
