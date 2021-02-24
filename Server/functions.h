#ifndef functions_h
#define functions_h


#include <iostream>
#include <sys/types.h>
#include <string.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <WinSock2.h>
#include <WS2tcpip.h>


using namespace std;


class Bank {
private:
    string name;
    int accountNo;
    int totalAmount;

public:
    Bank();

    string getBankName() {  return name; }
    int getAccountNo()  { return accountNo; }
    int getTotalAmount(){ return totalAmount; }
    void setBankName(string s) { name = s; }
    void setAccountNo(int i) { accountNo = i; }
    void setTotalAmount(int value) { totalAmount = value; }
};

class Person : public Bank 
{

private:
    string userName;
    string name;
    string surName;
    string password;
    
public:

    Person();

    string getUserName() {return userName;}
    string getName() {return name;}
    string getSurname() {return surName;}
    string getPassword() {return password;}

    void setUserName(string s) {userName = s;}
    void setName(string s) {name = s;}
    void setSurname(string s) {surName = s;}
    void setPassword(string s) {password = s;}

    static Person *dataBase();
    static Person *showAccountInfo(string userName);
};

class Functions
{
public:

    Functions();

    static int userNameCheck(string name);

    static int userPassCheck(string pass, string name);

    static int deposit(Person* clientPerson, int value);

    static int withdraw(Person* clientPerson, int value);

    static int transfer(Person* clientPerson, int accountNo, string tarName, string tarSurname, int value);

    static void addValuesFromTxt();

    static void addValuesToTxt();
};
#endif