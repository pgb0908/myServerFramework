//
// Created by bong on 22. 7. 15.
//

#ifndef MYSERVERFW_CUSTOMQUEUE_H
#define MYSERVERFW_CUSTOMQUEUE_H

#include <utility>
#include <memory>
#include "Queue.h"

template<typename T>
class MpscLockQueue : public Queue<T> {
public:
    MpscLockQueue()
    {
        head_ = nullptr;
        tail_ = nullptr;
    };

    ~MpscLockQueue(){
        T output;
        while (this->dequeue(output))
        {
        }
        std::shared_ptr<BufferNode> front = head_;
        front.reset();
    };

    void enqueue(T &&input) override {
        auto node = std::make_shared<BufferNode>(std::move(input));

        if(tail_ == nullptr){
            head_ = node;
            tail_ = node;

            return;
        }

        tail_->next_ = node;
        tail_ = node;
    }

    void enqueue(const T &input) override {
        auto node = std::make_shared<BufferNode>(std::move(input));
        if(tail_ == nullptr){
            head_ = node;
            tail_ = node;
            return;
        }
        tail_->next_ = node;
        tail_ = node;
    }

    bool dequeue(T &output) override {
        if(head_ == nullptr)return false;

        auto temp = head_;
        head_ = head_->next_;
        output = std::move(*(temp->dataPtr_));

        if(head_ == nullptr) tail_ = nullptr;

        return true;

    }

    bool empty() override {
        auto next = tail_;

        return next == nullptr;
    }

private:
    struct BufferNode
    {
        BufferNode() = default;
        BufferNode(const T &data) : dataPtr_(new T(data))
        {
        }
        BufferNode(T &&data) : dataPtr_(new T(std::move(data)))
        {
        }
        std::shared_ptr<T> dataPtr_;
        std::shared_ptr<BufferNode> next_{nullptr};
    };

    std::shared_ptr<BufferNode> head_;
    std::shared_ptr<BufferNode> tail_;

};




#endif //MYSERVERFW_CUSTOMQUEUE_H
