//
// Created by bong on 22. 6. 28.
//

#ifndef MYSERVERFW_TCPSERVER_H
#define MYSERVERFW_TCPSERVER_H

#include "InetAddress.h"

namespace net{

    class TcpServer{
    public:
        TcpServer()=default;

        TcpServer getAddress(InetAddress& address);

        TcpServer getName(std::string name);

        TcpServer getEventMgr();

        TcpServer getIoEventNum();

        void start();

    private:
        InetAddress address_;
        std::string name_;

    };
}



#endif //MYSERVERFW_TCPSERVER_H
