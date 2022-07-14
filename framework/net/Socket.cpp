//
// Created by bong on 22. 7. 14.
//

#include <cerrno>
#include "Socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include <cassert>
#include <cstring>
#include <iostream>

int Socket::getSocketError(int sockFd) {
    int optval;
    socklen_t optlen = static_cast<socklen_t>(sizeof optval);

    if(::getsockopt(sockFd, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0){
        return errno;
    }else{
        return optval;
    }
}

int Socket::createNonblockingSocket(int family) {
    int sock = ::socket(family,
                        SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,
                        IPPROTO_TCP);
    if (sock < 0)
    {
        exit(1);
    }
    return sock;
}

int Socket::connect(int sockFd, const InetAddress &addr) {
    if(addr.isIpV6()){
        return ::connect(sockFd,
                         addr.getSockAddr(),
                         static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
    }else{
        return ::connect(sockFd,
                         addr.getSockAddr(),
                         static_cast<socklen_t>(sizeof(struct sockaddr_in)));
    }
}

Socket::Socket(int sockFd) {
    sockFd_ = sockFd;

}

Socket::~Socket() {
    if(sockFd_ >= 0) close(sockFd_);
}

int Socket::getSockFd() const {
    return sockFd_;
}

void Socket::setSockFd(int sockFd) {
    sockFd_ = sockFd;
}

void Socket::bindAddress(const InetAddress &localaddr) {
    assert(sockFd_ > 0);

    int ret;
    if(localaddr.isIpV6()){
        ret = ::bind(sockFd_, localaddr.getSockAddr(), sizeof(sockaddr_in6));
    }else{
        ret = ::bind(sockFd_, localaddr.getSockAddr(), sizeof(sockaddr_in));
    }

    if(ret == 0){
        return;
    }else{
        exit(1);
    }
}

void Socket::listen() {
    assert(sockFd_ > 0);

    int ret = ::listen(sockFd_, SOMAXCONN);
    if(ret < 0){
        exit(1);
    }
}

int Socket::accept(InetAddress *peeraddr) {
    struct sockaddr_in6 addr6;
    memset(&addr6, 0, sizeof(addr6));
    socklen_t size = sizeof(addr6);

    int connfd = ::accept4(sockFd_,
                          (struct sockaddr *) &addr6,
                                  &size,
                          SOCK_NONBLOCK | SOCK_CLOEXEC);

    if (connfd >= 0)
    {
        peeraddr->setSockAddrInet6(addr6);
    }
    return connfd;
}

void Socket::closeWrite() {
    if (::shutdown(sockFd_, SHUT_WR) < 0){
        std::cout << "socket::shutdownWrite" << std::endl;
    }
}

int Socket::read(char *buffer, uint64_t len) {
    return ::read(sockFd_, buffer, len);
}

struct sockaddr_in6 Socket::getLocalAddr(int sockFd) {
    struct sockaddr_in6 localaddr;
    memset(&localaddr, 0, sizeof(localaddr));
    socklen_t addrlen = static_cast<socklen_t>(sizeof localaddr);
    if (::getsockname(sockFd,
                      static_cast<struct sockaddr *>((void *)(&localaddr)),
                      &addrlen) < 0)
    {
        std::cout << "socket::getLocalAddr, error occurred" << std::endl;
    }
    return localaddr;
}
