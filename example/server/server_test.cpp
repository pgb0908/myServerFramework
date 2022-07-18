//
// Created by bong on 22. 6. 28.
//

#include <iostream>
#include "../../framework/net/TcpServer.h"
#include "../../framework/net/InetAddress.h"
#include "../../framework/net/EventLoopThread.h"

using namespace std;

int main(){
    cout << "server example" << endl;

    InetAddress endpoint(13000);

    // MainLoop 생성
    EventLoopThread mainLoopThread;


    TcpServer server;

    server.Address(endpoint)
          .MainLoop(mainLoopThread.getLoop())
          //.IoEventNum(3)
          .Name("TCP-Server");

    server.start();

    std::cout << server.getIoLoopNum() << std::endl;

    mainLoopThread.wait();

    return 0;
}