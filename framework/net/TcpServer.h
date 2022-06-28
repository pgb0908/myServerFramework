//
// Created by bong on 22. 6. 28.
//

#ifndef MYSERVERFW_TCPSERVER_H
#define MYSERVERFW_TCPSERVER_H

namespace net{

    class TcpServer{
    public:
        TcpServer()=default;

        TcpServer getEndPoint();

        TcpServer getName();

        TcpServer getEventMgr();

        TcpServer getIoEventNum();

        void start();

    private:


    };
}



#endif //MYSERVERFW_TCPSERVER_H
