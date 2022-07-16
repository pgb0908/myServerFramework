//
// Created by bong on 22. 7. 15.
//

#ifndef MYSERVERFW_QUEUE_H
#define MYSERVERFW_QUEUE_H




template<typename T>
class Queue {
public:
    Queue() = default;
    virtual ~Queue() = default;

    virtual void enqueue(T &&input) = 0;

    virtual void enqueue(const T &input) = 0;

    virtual bool dequeue(T &output) = 0;

    virtual bool empty() = 0;

};

#endif //MYSERVERFW_QUEUE_H
