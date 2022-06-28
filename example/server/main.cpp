//
// Created by bong on 22. 6. 28.
//

#include <iostream>
#include "../../framework/net/TcpServer.h"

using namespace std;

int main(){
    cout << "server example" << endl;

    // EvnetManager 생성

    net::TcpServer server;

    server.getEndPoint().getEventMgr().getIoEventNum().getName();

    server.start();


    return 0;
}