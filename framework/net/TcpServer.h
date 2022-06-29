//
// Created by bong on 22. 6. 28.
//

#ifndef MYSERVERFW_TCPSERVER_H
#define MYSERVERFW_TCPSERVER_H

#include "InetAddress.h"
#include "MainLoopThread.h"

class TcpServer {
public:
    TcpServer() = default;

    TcpServer getAddress(InetAddress &address);

    TcpServer getName(std::string name);

    TcpServer getMainLoopThread(MainLoopThread& mainLoopThread);

    TcpServer getIoEventNum(int io_nums);

    void start();

private:
    InetAddress address_;
    std::string name_;
    int io_num_;

    MainLoopThread mainLoopThread_;

};


#endif //MYSERVERFW_TCPSERVER_H
