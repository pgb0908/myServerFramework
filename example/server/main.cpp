//
// Created by bong on 22. 6. 28.
//

#include <iostream>
#include "../../framework/net/TcpServer.h"
#include "../../framework/net/InetAddress.h"
#include "../../framework/net/MainLoopThread.h"

using namespace std;

int main(){
    cout << "server example" << endl;

    InetAddress endpoint(12000);

    // MainLoop 생성
    MainLoopThread mainLoopThread;


    TcpServer server;
    server.getAddress(endpoint).getMainLoopThread(mainLoopThread).getIoEventNum(1).getName("TCP-Server");

    server.start();


    return 0;
}