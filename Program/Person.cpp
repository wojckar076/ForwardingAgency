#include "Person.h"

Person::Person() : name("-"), lastname("-"), phoneNumber("-") {}	

Person::Person(string i, string n, string phone) : name(i), lastname(n), phoneNumber(phone) {}

Person::~Person() {}		

void Person::setName(string newName)
{
	this->name = newName;
}

void Person::setLastname(string newLastname)
{
	this->lastname = newLastname;
}

void Person::setPhoneNumber(string newPhoneNumber)
{
	this->phoneNumber = newPhoneNumber;
}

string Person::getName() { return name; }

string Person::getLastname() { return lastname; }

string Person::getPhoneNumber() { return phoneNumber; }