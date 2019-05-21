#include "Employee.h"

Employee::Employee(int id, string name, string lastname, string phone, string login, string password)
	:Person(name, lastname, phone), BaseEntity(id), login(login), password(password) {}

string Employee::getPassword() { return password; }

string Employee::getLogin() { return login; }

int Employee::getID() { return id; }

void Employee::setLogin(string newLogin)
{
	this->login = newLogin;
}

void Employee::setPassword(string newPassword)
{
	this->password = newPassword;
}

