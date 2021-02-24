//Mehmet Kas
#pragma once
#include "client.h"


#include <iostream>
#include <sys/types.h>
#include <string>
#include <time.h>
#include <thread>
#include <WinSock2.h>
#include <ws2tcpip.h>

using namespace std;



int main()
{

    Client client;
    client.connectToServer();

    return 0;

}