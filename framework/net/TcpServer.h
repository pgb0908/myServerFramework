//
// Created by bong on 22. 6. 28.
//

#ifndef MYSERVERFW_TCPSERVER_H
#define MYSERVERFW_TCPSERVER_H

#include "InetAddress.h"
#include "MainLoopThread.h"

class TcpServer {
public:
    TcpServer();

    TcpServer& Address(InetAddress &address);

    TcpServer& Name(std::string name);

    TcpServer& MainLoop(std::shared_ptr<EventLoop> loop);

    TcpServer& IoEventNum(int io_nums);

    int getIoLoopNum() const{
        return io_num_;
    }

    void start();

private:
    InetAddress address_;
    std::string name_;
    int io_num_;

    std::shared_ptr<EventLoop> mainLoop_;

};


#endif //MYSERVERFW_TCPSERVER_H
