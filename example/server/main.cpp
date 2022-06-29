//
// Created by bong on 22. 6. 28.
//

#include <iostream>
#include "../../framework/net/TcpServer.h"
#include "../../framework/net/InetAddress.h"

using namespace std;

int main(){
    cout << "server example" << endl;

    // EvnetManager 생성

    net::TcpServer server;

    net::InetAddress endpoint(12000);

    server.getAddress(endpoint).getEventMgr().getIoEventNum().getName("TCP-Server");

    server.start();


    return 0;
}