#pragma once
#include "Person.h"
#include "BaseEntity.h"
#include "CommonTypedefs.h"
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

class Employee : public Person, public BaseEntity {
private:
	string login;
	string password;
public:
	Employee(int, string, string, string, string, string);
	void setLogin(string);
	void setPassword(string);
	int getID();
	string getLogin();
	string getPassword();

	friend ostream& operator<<(ostream& os, const Employee& emp)
	{
		os << "ID: " << emp.id << endl;
		os << "Name: " << emp.name << endl;
		os << "Lastname: " << emp.lastname << endl;
		os << "Phone:" << emp.phoneNumber << endl;
		os << "Login:" << emp.login << endl << endl;
		return os;
	}
};