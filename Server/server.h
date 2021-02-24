#pragma once


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <sys/types.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <thread>
#include <vector>
#include "functions.h"

using namespace std;


class Server
{
public:

    Server();

    string error = "error";
    string correct = "correct";
    int bytesReceived;
    string response = "1";


    void Socket();

    int serverProcess(SOCKET clientSocket);

    string transfer(int clientSocket, Person* person, char* buf);

    string withdraw(int clientSocket, Person* person, char* buf);

    string tryingToLogin(string name, int clientSocket, char* buf);

    string deposit(int clientSocket, Person* person, char* buf);

    void showInfo(int clientSocket, Person* person, char* buf);

    int createServerSocket();

    int newSocket(SOCKET ServerSocket);

    string waitingChoice(int clientSocket, char* buf);

    Functions function;

};

