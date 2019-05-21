#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iomanip>

using namespace std;

class Person {
protected:
	string name;
	string lastname;
	string phoneNumber;

public:
	Person();		
	Person(string, string, string);
	~Person();
	//setters & getters
	void setName(string);
	void setLastname(string);
	void setPhoneNumber(string);
	string getName();
	string getLastname();
	string getPhoneNumber();
};