//
// Created by bong on 22. 6. 29.
//

#ifndef MYSERVERFW_MAINLOOPTHREAD_H
#define MYSERVERFW_MAINLOOPTHREAD_H

#include <string>

class MainLoopThread {
public:
    explicit MainLoopThread(const std::string& threadName = "MainLoopThead");

    void run();
    void wait();

private:
    std::string threadName_;
};


#endif //MYSERVERFW_MAINLOOPTHREAD_H
