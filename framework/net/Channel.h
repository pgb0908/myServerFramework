//
// Created by bong on 22. 6. 29.
//

#ifndef MYSERVERFW_CHANNEL_H
#define MYSERVERFW_CHANNEL_H


#include <functional>
#include "EventLoop.h"

class Channel {
    using EventCallback = std::function<void()>;
public:
    Channel(EventLoop* loop, int fd);

    /**
     * @brief Set the read callback.
     *
     * @param cb The callback is called when read event occurs on the socket.
     * @note One should call the enableReading() method to ensure that the
     * callback would be called when some data is received on the socket.
     */
    void setReadCallback(const EventCallback &cb)
    {
        readCallback_ = cb;
    };
    void setReadCallback(EventCallback &&cb)
    {
        readCallback_ = std::move(cb);
    }

    /**
     * @brief Set the write callback.
     *
     * @param cb The callback is called when write event occurs on the socket.
     * @note One should call the enableWriting() method to ensure that the
     * callback would be called when the socket can be written.
     */
    void setWriteCallback(const EventCallback &cb)
    {
        writeCallback_ = cb;
    };
    void setWriteCallback(EventCallback &&cb)
    {
        writeCallback_ = std::move(cb);
    }

    /**
     * @brief Set the close callback.
     *
     * @param cb The callback is called when the socket is closed.
     */
    void setCloseCallback(const EventCallback &cb)
    {
        closeCallback_ = cb;
    }
    void setCloseCallback(EventCallback &&cb)
    {
        closeCallback_ = std::move(cb);
    }

    /**
     * @brief Set the error callback.
     *
     * @param cb The callback is called when an error occurs on the socket.
     */
    void setErrorCallback(const EventCallback &cb)
    {
        errorCallback_ = cb;
    }
    void setErrorCallback(EventCallback &&cb)
    {
        errorCallback_ = std::move(cb);
    }

    /**
     * @brief Set the event callback.
     *
     * @param cb The callback is called when any event occurs on the socket.
     * @note If the event callback is set to the channel, any other callback
     * wouldn't be called again.
     */
    void setEventCallback(const EventCallback &cb)
    {
        eventCallback_ = cb;
    }
    void setEventCallback(EventCallback &&cb)
    {
        eventCallback_ = std::move(cb);
    }

    /**
     * @brief Check whether there is no event enabled on the socket.
     *
     * @return true
     * @return false
     */
    bool isNoneEvent() const
    {
        return events_ == kNoneEvent;
    };

    /**
     * @brief Disable all events on the socket.
     *
     */
    void disableAll()
    {
        events_ = kNoneEvent;
        update();
    }

    /**
     * @brief Remove the socket from the poller in the event loop.
     *
     */
    void remove();

    /**
     * @brief Enable the read event on the socket.
     *
     */
    void enableReading()
    {
        events_ |= kReadEvent;
        update();
    }

    /**
     * @brief Disable the read event on the socket.
     *
     */
    void disableReading()
    {
        events_ &= ~kReadEvent;
        update();
    }

    /**
     * @brief Enable the write event on the socket.
     *
     */
    void enableWriting()
    {
        events_ |= kWriteEvent;
        update();
    }

    /**
     * @brief Disable the write event on the socket.
     *
     */
    void disableWriting()
    {
        events_ &= ~kWriteEvent;
        update();
    }

    /**
     * @brief Check whether the write event is enabled on the socket.
     *
     * @return true
     * @return false
     */
    bool isWriting() const
    {
        return events_ & kWriteEvent;
    }

    /**
     * @brief Check whether the read event is enabled on the socket.
     *
     * @return true
     * @return false
     */
    bool isReading() const
    {
        return events_ & kReadEvent;
    }

    /**
     * @brief Set and update the events enabled.
     *
     * @param events
     */
    void updateEvents(int events)
    {
        events_ = events;
        update();
    }

    int getFd() const {
        return fd_;
    }

    int getEvents() const {
        return events_;
    }

    void setEvents(int events) {
        events_ = events;
    }

    int getIndex() const {
        return index_;
    }

    void setIndex(int index) {
        index_ = index;
    }

    void handleEvent();
    void handleEventSafely();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

private:
    void update();

    int setRevents(int revt)
    {
        revents_ = revt;
        return revt;
    };

    EventLoop *loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;
    bool addedToLoop_{false};
    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
    EventCallback closeCallback_;
    EventCallback eventCallback_;
    std::weak_ptr<void> tie_;
    bool tied_;

};


#endif //MYSERVERFW_CHANNEL_H
