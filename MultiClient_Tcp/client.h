#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <WS2tcpip.h>
#include <conio.h>
#include <time.h>


using namespace std;


class Client
{
public:

	Client();

	char buf[4096];
	string user;
	int i = 0;
	bool booleannn = true;
	string error = "error";
	string correct = "correct";
	int  bytesReceived;
	string choiceStr, response = "1", choice;


	int clientProcess(int sock, string check);

	bool check_number(string str);

	string clientTransfer(int sock);

	string clientWithdraw(int sock);

	string clientDeposit(int sock);

	string clientShowInfo(int sock);

	int userChoice();

	string clientEntryCheck(int sock);

	string connectToServer();

};