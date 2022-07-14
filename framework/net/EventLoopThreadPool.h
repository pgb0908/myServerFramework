//
// Created by bong on 22. 7. 13.
//

#ifndef MYSERVERFW_EVENTLOOPTHREADPOOL_H
#define MYSERVERFW_EVENTLOOPTHREADPOOL_H


class EventLoopThreadPool {
public:
    explicit EventLoopThreadPool(int io_num);
    void start();

};


#endif //MYSERVERFW_EVENTLOOPTHREADPOOL_H
