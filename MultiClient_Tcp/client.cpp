#pragma once
#include "client.h"


// Project -> Linker -> Additional Dependencies 
// Ws2_32.lib

Client::Client()
{

}

int Client::clientProcess(int sock, string check)
{
	do
	{
		if (check == correct)
		{
			std::cout << "" << endl;
			std::cout << "--Giris islemi Basarili--" << endl;

			booleannn = false;
			bool control = true;
			
			do
			{
				int choices = userChoice();
			functionCase:
				switch (choices)
				{
				case 1:
					clientShowInfo(sock);
				break;

				case 2:
					if (clientDeposit(sock) == error) { choices = 5; goto functionCase; };
				break;

				case 3:
					if (clientWithdraw(sock) == error) { choices = 5; goto functionCase;};
				break;

				case 4:
				{
					if (clientTransfer(sock) == error) { choices = 5; goto functionCase; };
				}
				break;

				case 5:
				{
				
					std::cout << "Cikis Yapiliyor.." << endl;
					std::cout << " " << endl;
					send(sock, to_string(choices).c_str(), to_string(choices).size() + 1, 0);
					return 0;
				}
				break;
				}

			} while (control);
		}
		else {

			cout << "Kullanici Girisi Basarisiz! Kullanici adi veya parola hatali." << endl;
			break;

		}
	} while (booleannn);

	cout << "cikis Yapiliyor.." << endl;
	return 0;

}

bool Client::check_number(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}

string Client::clientTransfer(int sock)
{
	string tarName, tarSurname, noStr, valueStr, targetNo, value;
	bool check = false;

	send(sock, choice.c_str(), choice.size() + 1, 0);
	bytesReceived = recv(sock, buf, 4096, 0);

	string oldValue = (string(buf, 0, bytesReceived));
	cout << "***Farkli banka ile yapilan islemlerde $5 islem ucreti olarak gondericiden alinir.***" << endl;
	cout << "" << endl;
	cout << "Hesap Bakiyeniz: $" << oldValue << endl;

	do {
		cout << "Para Gonderilecek Hesap No: ";

		clock_t start = clock();

		while (!_kbhit()) //Check for keyboard hit
		{
			//Check if 60 sec timer expired or not
			if (((clock() - start) / CLOCKS_PER_SEC) >= 60)
			{
				cout << endl << endl << "Gecerli bir islem yapmadiniz. Timed Out!" << endl;
				return error;
			}
		}
		cin >> targetNo;

		if (!check_number(targetNo)) { cout << "Yanlis bir karakter girdiniz!" << endl; check = true; }
		else { check = false; }

	} while (check);

	send(sock, targetNo.c_str(), targetNo.size() + 1, 0);
	bytesReceived = recv(sock, buf, 4096, 0);

	cout << "Para Gonderilecek Kisi ismi: ";
	cin >> tarName;

	send(sock, tarName.c_str(), tarName.size() + 1, 0);
	bytesReceived = recv(sock, buf, 4096, 0);

	cout << "Para Gonderilecek Kisi Soyismi: ";
	cin >> tarSurname;

	send(sock, tarSurname.c_str(), tarSurname.size() + 1, 0);
	bytesReceived = recv(sock, buf, 4096, 0);

	do {
		cout << "Gondermek Istenen Para Miktari: $";

		clock_t start = clock();

		while (!_kbhit()) //Check for keyboard hit
		{
			//Check if 60 sec timer expired or not
			if (((clock() - start) / CLOCKS_PER_SEC) >= 60)
			{
				cout << endl << endl << "Gecerli bir islem yapmadiniz. Timed Out!" << endl;
				return error;
			}
		}
		cin >> value;

		if (!check_number(value)) { cout << "Yanlis bir karakter girdiniz!" << endl; check = true; }
		else { check = false; }

	} while (check);

	send(sock, value.c_str(), value.size() + 1, 0);
	bytesReceived = recv(sock, buf, 4096, 0);

	string bakiyeLast = (string(buf, 0, bytesReceived));
	int bakiyeInt = stoi(bakiyeLast);
	if (bakiyeInt == -1)
	{
		cout << "" << endl;
		cout << "Yanlis hesap Bilgileri girildi." << endl;
		return error;
	}
	else if (bakiyeInt == -2)
	{
		cout << "Hesabinizda yeterli bakiye bulunmamaktadir." << endl;
		return error;
	}
	else {
		cout << "Hesap Bakiyeniz: $" << bakiyeLast << endl;
	}
	return correct;
}

string Client::clientWithdraw(int sock)
{
	string value = "0";
	bool check = false;

	send(sock, choice.c_str(), choice.size() + 1, 0);
	bytesReceived = recv(sock, buf, 4096, 0);

	if (bytesReceived == -1 || bytesReceived == 0)
	{
		cout << "Server Disconnected." << endl;
		return error;
	}

	string oldValue = (string(buf, 0, bytesReceived));
	int toplamBakiye = stoi(oldValue);
	do {
		if (stoi(value) > toplamBakiye)
		{
			cout << "Hesabinizda bulunandan daha fazla bir miktar girdiniz!" << endl;
		}
		cout << "Hesap Bakiyeniz: " << oldValue << endl;
		cout << "" << endl;
		do
		{
			cout << "Lutfen cekmek istediginiz tutari giriniz: ";

			clock_t start = clock();

			while (!_kbhit()) //Check for keyboard hit
			{
				//Check if 60 sec timer expired or not
				if (((clock() - start) / CLOCKS_PER_SEC) >= 60)
				{
					cout << endl << endl << "Gecerli bir islem yapmadiniz. Timed Out!" << endl;
					return error;
				}
			}

			cin >> value;

			if (!check_number(value)) { cout << "Yanlis bir karakter girdiniz!" << endl; check = true; }
			else { check = false; }
		} while (check);
		

		cout << "" << endl;
	} while (stoi(value) > toplamBakiye);

	send(sock, value.c_str(), value.size() + 1, 0);
	bytesReceived = recv(sock, buf, 4096, 0);

	if (bytesReceived == -1 || bytesReceived == 0)
	{
		cout << "Server Disconnected." << endl;
		return error;
	}


	toplamBakiye = stoi((string(buf, 0, bytesReceived)));
	if (toplamBakiye != -1) {
		cout << "Hesap Bakiyeniz: " << (string(buf, 0, bytesReceived)) << endl;
	}
	cout << "" << endl;
	return correct;
}

string Client::clientDeposit(int sock)
{
	string value;
	bool check = true;

	send(sock, choice.c_str(), choice.size() + 1, 0);
	bytesReceived = recv(sock, buf, 4096, 0);

	if (bytesReceived == -1 || bytesReceived == 0)
	{
		cout << "Server Disconnected." << endl;
		return error;
	}

	cout << "Hesap Bakiyeniz: " << (string(buf, 0, bytesReceived)) << endl;
	cout << "" << endl;
	do {
		cout << "Lutfen yatirmak istediginiz tutari giriniz: ";

		clock_t start = clock();

		while (!_kbhit()) //Check for keyboard hit
		{
			//Check if 60 sec timer expired or not
			if (((clock() - start) / CLOCKS_PER_SEC) >= 60)
			{
				cout << endl << endl << "Gecerli bir islem yapmadiniz. Timed Out!" << endl;
				return error;
			}
		}

		cin >> value;

		if (!check_number(value)) { cout << "Yanlis bir karakter girdiniz!" << endl; check = true; }
		else { check = false; }

	} while (check);
	

	cout << "" << endl;
	send(sock, value.c_str(), value.size() + 1, 0);
	bytesReceived = recv(sock, buf, 4096, 0);

	if (bytesReceived == -1 || bytesReceived == 0)
	{
		cout << "Server Disconnected." << endl;
		return error;
	}

	cout << "Hesap Bakiyeniz: " << (string(buf, 0, bytesReceived)) << endl;
	cout << "" << endl;

	return correct;
}

string Client::clientShowInfo(int sock)
{

	send(sock, choice.c_str(), choice.size() + 1, 0);
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			cout << "Isim: ";
		}
		else if (i == 1)
		{
			cout << "Soyisim: ";
		}
		else if (i == 2)
		{
			cout << "Banka Adi: ";
		}
		else if (i == 3)
		{
			cout << "Hesap Numarasi: ";
		}
		else
		{
			cout << "Hesap Bakiyesi: $";

		}
		bytesReceived = recv(sock, buf, 4096, 0);

		if (bytesReceived == -1 || bytesReceived == 0)
		{
			cout << "Server Disconnected." << endl;
			return error;
		}

		cout << string(buf, 0, bytesReceived) << endl;
		send(sock, response.c_str(), response.size() + 1, 0);

	}
	return correct;
}

int Client::userChoice()
{
	do
	{
		cout << "" << endl;
		cout << "1-Hesap Bilgilerini Gosterme." << endl;
		cout << "2-Hesaba Para Yatirma." << endl;
		cout << "3-Hesaptan Para cekme." << endl;
		cout << "4-Baska Hesaba Para Yatirma." << endl;
		cout << "5-Quit." << endl;
		cout << "" << endl;
		cout << "Lutfen yapmak istediginiz islem numarasini giriniz: ";

		clock_t start = clock();

		while (!_kbhit()) //Check for keyboard hit
		{
			//Check if 60 sec timer expired or not
			if (((clock() - start) / CLOCKS_PER_SEC) >= 60)
			{
				cout << endl << endl <<"Gecerli bir islem yapmadiniz. Timed Out!" << endl;
				return 5;
			}
		}

		cin >> choice;


		if (!check_number(choice)) { cout << "Yanlis bir karakter girdiniz!" << endl; cout << "" << endl; choice = '0'; }
		else if (stoi(choice) <= 0 || stoi(choice) >= 6)
		{
			cout << "Yanlis bir secim yapildi.Yeniden Deneyin." << endl;
			cout << "" << endl;
		}

	} while (stoi(choice) <= 0 || stoi(choice) >= 6);

	return stoi(choice);
}

string Client::clientEntryCheck(int sock)
{
	cout << "Username: ";
	cin >> user;

	int sendRes = send(sock, user.c_str(), user.size() + 1, 0);

	if (sendRes == -1)
	{
		cout << "Could not send to server! Whoops!\r\n";
		return error;
	}

	
	memset(buf, 0, 4096);
	string gelen;
	int bytesReceived = recv(sock, buf, 4096, 0);

	gelen = string(buf, 0, bytesReceived);
	
	if (gelen == error) {

	}


	cout << "Password: ";
	cin >> user;

	send(sock, user.c_str(), user.size() + 1, 0);
	bytesReceived = recv(sock, buf, 4096, 0);

	string tempName= (string(buf, 0, bytesReceived));

	clientProcess(sock, tempName);
	
	return correct;
}

string Client::connectToServer()
{
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr;
	SOCKET client;
	int sock;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(54000);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		cout << "Can't create socket!" << endl;
		return error;
	}

	

	int connectRes = connect(sock, (sockaddr*)&addr, sizeof(addr));
	if (connectRes == -1)
	{
		return error;
	}
	while(true)
		clientEntryCheck(sock);


	return correct;

}
