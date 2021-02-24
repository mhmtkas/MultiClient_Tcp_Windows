#include "functions.h"

//Mehmet Kas

Functions::Functions()
{

}

Person::Person()
{

}

Bank::Bank()
{

}

Person * Person::dataBase()
{
	static Person client1;
	static Person client2;
	static Person client3;
	static Person client4;
	static Person client5;
	static Person client6;

	static Person arrayPerson[6] = { client1,client2,client3 ,client4,client5,client6 };
	return arrayPerson;
}

int Functions::userNameCheck(string name)
{
	Person *arrayPerson;
	arrayPerson = Person::dataBase();
	int tmp = 0;

	string isim;
	for (int i = 0; i < 6; i++) {
		isim = (arrayPerson + i)->getUserName();
		if ((name) == (isim)) {
			return 1;
		}
	}
	cout << "Wrong Username" << endl;
	return 0;
}

int Functions::userPassCheck(string pass, string name)
{
	Person* arrayPerson;
	arrayPerson = Person::dataBase();

	string password;
	string isim;
	for (int i = 0; i < 6; i++) {
		isim = (arrayPerson + i)->getUserName();

		if ((name) == (isim)) {
			password = (arrayPerson + i)->getPassword();

			if ((pass) == (password)) {
				cout << "Correct Password" << endl;
				cout << "Login Process Succesfull." << endl;
				return 1;
			}
		}
	}
	cout << "Wrong Password" << endl;
	cout << "Login Failed." << endl;
	return 0;
}

Person *Person::showAccountInfo(string userName)
{
	Person *p;

	p = Person::dataBase();

	string isim;

	for (int i = 0; i < 6; i++) {

		isim = (p+i)->getUserName();
		if ((userName) == (isim)) {
			return (p + i);

		}
	}
	return NULL;
}

int Functions::deposit(Person* clientPerson, int value)
{

	clientPerson->setTotalAmount(clientPerson->getTotalAmount()+value);

	return clientPerson->getTotalAmount();
}

int Functions::withdraw(Person* clientPerson, int value)
{
	
	clientPerson->setTotalAmount(clientPerson->getTotalAmount() - value);

	return clientPerson->getTotalAmount();
}

int Functions::transfer(Person* clientPerson, int accountNo, string tarName, string tarSurname, int value)
{
	addValuesFromTxt();
	Person* p;
	p = Person::dataBase();
	string isim, gidenIsim, gidenSoyisim;
	int userValue, bankaNo, gidenValue, islemUcreti = 0;
	int  locationTar = -1;

	userValue = clientPerson->getTotalAmount();

	transform(tarName.begin(), tarName.end(), tarName.begin(), ::toupper);
	transform(tarSurname.begin(), tarSurname.end(), tarSurname.begin(), ::toupper);


	for (int i = 0; i < 6; i++) {

		bankaNo = (p + i)->getAccountNo();

		gidenIsim = (p + i)->getName();

		gidenSoyisim = (p + i)->getSurname();

		transform(gidenIsim.begin(), gidenIsim.end(), gidenIsim.begin(), ::toupper);
		transform(gidenSoyisim.begin(), gidenSoyisim.end(), gidenSoyisim.begin(), ::toupper);


		if ((accountNo == bankaNo) && (gidenIsim == tarName) && (gidenSoyisim == tarSurname)) {
			locationTar = i;
			break;
		}
	}
	if (locationTar == -1) {
		return -1;
	}
	if (clientPerson->getBankName() != (p + locationTar)->getBankName())
	{
		islemUcreti = 5;
	}

	if (userValue >= (value + islemUcreti))
	{
		if (islemUcreti > 0)
		{
			clientPerson->setTotalAmount((clientPerson->getTotalAmount()) - (value + islemUcreti));
			(p + locationTar)->setTotalAmount((p + locationTar)->getTotalAmount() + (value));
			Functions::addValuesToTxt(); 
			return clientPerson->getTotalAmount();
		}

		clientPerson->setTotalAmount((clientPerson->getTotalAmount()) - (value));
		(p + locationTar)->setTotalAmount(((p + locationTar)->getTotalAmount()) + (value));

		Functions::addValuesToTxt();

		return clientPerson->getTotalAmount();

	}
	else
	{
		return -2;
	}

}

void Functions::addValuesFromTxt()
{
	Person  *arrayPerson;
	arrayPerson = Person::dataBase();

	string userName, name, surname, password, bankaName;
	int hesapNo, paraValue;

	fstream dosyaOku("database.txt");
	string satir = "";
	if (dosyaOku.is_open()) {

		for (int i = 0; i < 6; i++) {
			
			dosyaOku >> userName >> name >> surname >> password >> bankaName >> hesapNo >> paraValue;
			
			(arrayPerson + i)->setUserName(userName);
			(arrayPerson + i)->setName(name);
			(arrayPerson + i)->setSurname(surname);
			(arrayPerson + i)->setPassword(password);
			(arrayPerson + i)->setBankName(bankaName);
			(arrayPerson + i)->setAccountNo(hesapNo);
			(arrayPerson + i)->setTotalAmount(paraValue);
		}
		dosyaOku.close();
	}
	else {
		cout << "dosya okunamadý";
	}

}

void Functions::addValuesToTxt()
{
	Person* arrayPerson;
	arrayPerson = Person::dataBase();

	string userName, name, surname, password, bankaName;
	int hesapNo, paraValue;

	fstream dosyaOku("database.txt", ios::out | ios::ate);
	string satir = "";

	if (dosyaOku.is_open()) {

		for (int i = 0; i < 6; i++) {
			userName = (arrayPerson + i)->getUserName();
			name = (arrayPerson + i)->getName();
			surname = (arrayPerson + i)->getSurname();
			password = (arrayPerson + i)->getPassword();
			bankaName = (arrayPerson + i)->getBankName();
			hesapNo = (arrayPerson + i)->getAccountNo();
			paraValue = (arrayPerson + i)->getTotalAmount();

			dosyaOku << userName << " " << name << " " << surname << " " << password << " " << bankaName << " " << hesapNo << " " << paraValue << endl;
		}
		dosyaOku.close();
	}
	

}
