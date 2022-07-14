//
// Created by bong on 22. 6. 29.
//

#include "MainLoopThread.h"
#include <utility>

MainLoopThread::MainLoopThread(std::string threadName):
                        threadName_(std::move(threadName))
{
    loop_ = new EventLoop;
}
