//
// Created by bong on 22. 7. 14.
//

#ifndef MYSERVERFW_SOCKET_H
#define MYSERVERFW_SOCKET_H


#include "InetAddress.h"

class Socket {
public:
    explicit Socket(int sockFd);
    ~Socket();


    static int createNonblockingSocket(int family);
    static int getSocketError(int sockFd);
    static int connect(int sockFd, const InetAddress& addr);
    static struct sockaddr_in6 getLocalAddr(int sockFd);

    void bindAddress(const InetAddress &localaddr);
    void listen();
    int accept(InetAddress *peeraddr);
    void closeWrite();
    int read(char *buffer, uint64_t len);

    int getSockFd() const;
    void setSockFd(int sockFd);

private:
    int sockFd_;

};


#endif //MYSERVERFW_SOCKET_H
