#pragma once
#include "server.h"


Server::Server()
{

}

int Server::serverProcess(SOCKET clientSocket)
{
	char buf[4096];
	
	while(true)
	{
		bool control = true;
		memset(buf, 0, 4096);

		int bytesReceivedName = recv(clientSocket, buf, 4096, 0);

		if (bytesReceivedName == 0 || bytesReceivedName == -1) { function.addValuesToTxt(); std::cout << "Client disconnected " << endl; break; }

		string name = (string(buf, 0, bytesReceivedName));

		std::cout << "Trying to Login: " << name << endl;

		Person *clientPerson;
		
		clientPerson = Person::showAccountInfo(name);
		
		if (function.userPassCheck(tryingToLogin(name, clientSocket, buf), name)) // checking password correct or not
		{
			//string choice;
			send(clientSocket, correct.c_str(), correct.size() + 1, 0);

			do
			{
				int choiceInt;

				string check = waitingChoice(clientSocket, buf);

				if (check == error) { break; }
				else { choiceInt = stoi(check); }


				cout << choiceInt << endl;
				cout << " " << endl;

				function.addValuesFromTxt();

				switch (choiceInt)
				{
				case 1:
					showInfo(clientSocket, clientPerson, buf);   //show user's info
					break;

				case 2:
					if (deposit(clientSocket, clientPerson, buf) == error) { control = false; }; // make deposit
					break;

				case 3:
					if (withdraw(clientSocket, clientPerson, buf) == error) { control = false; };
					break;

				case 4:
					if (transfer(clientSocket, clientPerson, buf) == error) { control = false; };
					break;
				case 5:
					control = false;
					break;
				}
			} while (control);
		}
		else
		{
			send(clientSocket, error.c_str(), error.size() + 1, 0);
			continue;
		}
	} 
	return 0;
}

void Server::Socket()
{
	// Create a socket
	SOCKET ServerSocket = createServerSocket();

	// Wait for a connection

	while (1)
	{
		function.addValuesFromTxt();

		// create new socket for every new client

		SOCKET clientSocket = newSocket(ServerSocket);

		thread threadProcess(&Server::serverProcess, this, clientSocket);
		threadProcess.detach();

	}
}

string Server::transfer(int clientSocket, Person* person, char* buf)
{
	function.addValuesFromTxt();

	cout << "***Starting Transfer Process***" << endl;
	cout << " " << endl;

	string money = to_string(person->getTotalAmount());

	send(clientSocket, money.c_str(), money.size() + 1, 0);
	bytesReceived = recv(clientSocket, buf, 4096, 0);


	int targetNo = stoi(string(buf, 0, bytesReceived));

	send(clientSocket, response.c_str(), response.size() + 1, 0);
	bytesReceived = recv(clientSocket, buf, 4096, 0);

	string tarName = (string(buf, 0, bytesReceived));

	send(clientSocket, response.c_str(), response.size() + 1, 0);
	bytesReceived = recv(clientSocket, buf, 4096, 0);


	string tarSurname = (string(buf, 0, bytesReceived));

	send(clientSocket, response.c_str(), response.size() + 1, 0);
	bytesReceived = recv(clientSocket, buf, 4096, 0);


	int value = stoi(string(buf, 0, bytesReceived));

	int snc = function.transfer(person, targetNo, tarName, tarSurname, value);

	string sncStr = to_string(snc);

	send(clientSocket, sncStr.c_str(), sncStr.size() + 1, 0);

	function.addValuesToTxt();

	return correct;
}

string Server::withdraw(int clientSocket, Person* clientPerson, char* buf)
{
	function.addValuesFromTxt();

	cout << "***Starting Withdraw Process***" << endl;
	cout << " " << endl;

	send(clientSocket, to_string(clientPerson->getTotalAmount()).c_str(), to_string(clientPerson->getTotalAmount()).size() + 1, 0);
	bytesReceived = recv(clientSocket, buf, 4096, 0);

	if (bytesReceived == 0 || bytesReceived == -1){function.addValuesToTxt();cout << "Client disconnected " << endl;return error;}

	int value = stoi(string(buf, 0, bytesReceived));

	int totalValue = function.withdraw(clientPerson, value);

	string valueStr = to_string(totalValue);

	send(clientSocket, valueStr.c_str(), valueStr.size() + 1, 0);
	function.addValuesToTxt();
	return correct;
}

string Server::tryingToLogin(string name, int clientSocket, char* buf)
{
	
	if (function.userNameCheck(name)) {
		cout << "Correct Username" << endl;
	}

	send(clientSocket, correct.c_str(), correct.size() + 1, 0);
	bytesReceived = recv(clientSocket, buf, 4096, 0);
	return (string(buf, 0, bytesReceived));
}

string Server::waitingChoice(int clientSocket, char* buf)
{
	cout << "Waiting for choice: ";
	cout << " " << endl;
	int bytesReceivedPass = recv(clientSocket, buf, 4096, 0);

	if (bytesReceivedPass == -1)
	{
		function.addValuesToTxt();
		cerr << "Error in recv(). Quitting" << endl;
		return error;
	}
	if (bytesReceivedPass == 0)
	{
		function.addValuesToTxt();
		cout << "Client disconnected " << endl;
		return error;
	}

	return (string(buf, 0, bytesReceivedPass));
}

string Server::deposit(int clientSocket, Person* clientPerson, char* buf)
{
	function.addValuesFromTxt();
	cout << "***Starting Deposit Process***" << endl;
	cout << " " << endl;

	send(clientSocket, to_string(clientPerson->getTotalAmount()).c_str(), to_string(clientPerson->getTotalAmount()).size() + 1, 0);
	int bytesReceived = recv(clientSocket, buf, 4096, 0);

	if (bytesReceived == 0 || bytesReceived == -1){function.addValuesToTxt();cout << "Client disconnected " << endl;return error;}

	int value = stoi(string(buf, 0, bytesReceived));
	int totalValue = function.deposit(clientPerson, value);
	string valueStr = to_string(totalValue);


	send(clientSocket, valueStr.c_str(), valueStr.size() + 1, 0);
	function.addValuesToTxt();
	return correct;
}

void Server::showInfo(int clientSocket, Person* person, char* buf)
{
	function.addValuesFromTxt();

	cout << "***Showing Account Info***" << endl;
	cout << " " << endl;

	send(clientSocket, person->getName().c_str(), person->getName().size() + 1, 0);
	recv(clientSocket, buf, 4096, 0);

	send(clientSocket, person->getSurname().c_str(), person->getSurname().size() + 1, 0);
	recv(clientSocket, buf, 4096, 0);

	send(clientSocket, person->getBankName().c_str(), person->getBankName().size() + 1, 0);
	recv(clientSocket, buf, 4096, 0);

	send(clientSocket, to_string(person->getAccountNo()).c_str(), to_string(person->getAccountNo()).size() + 1, 0);
	recv(clientSocket, buf, 4096, 0);

	send(clientSocket, to_string(person->getTotalAmount()).c_str(), to_string(person->getTotalAmount()).size() + 1, 0);
	recv(clientSocket, buf, 4096, 0);


	
}

int Server::createServerSocket()
{

	SOCKET ServerSocket;
	WSADATA wsa;
	int iResult;
	sockaddr_in addr;
	SOCKET sock, client;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(54000);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	iResult = WSAStartup(MAKEWORD(2, 2), &wsa);

	if (iResult) {
		cout << "WSA Startup Failed.";
		return 0;
	}
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		exit(1);
	}

	// Bind the ip address and port to a socket

	bind(ServerSocket, (sockaddr*)&addr, sizeof(addr));


	listen(ServerSocket, SOMAXCONN);
	cout << "Server is waiting.." << endl;
	return ServerSocket;
}

int Server::newSocket(SOCKET ServerSocket)
{
	sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	SOCKET clientSocket = accept(ServerSocket, (sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET) {
		cout << "Can't accept a client! Error:";
		closesocket(ServerSocket);
		WSACleanup();

	}

	char host[NI_MAXHOST];      // Client's remote name
	char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on

	memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " << ntohs(client.sin_port) << endl;
	}
	return clientSocket;

}

