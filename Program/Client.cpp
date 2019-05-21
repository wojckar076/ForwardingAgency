#include "Client.h"

Client::Client(int _id, string name, string lastname, string phoneNumber, string _parcels)
	:Person(name, lastname, phoneNumber), BaseEntity(_id), parcels(_parcels) 
{
	setParIDContainer(_parcels);
}


Client::Client(int _id, string _name, string _lastname, string _phone) : Person(_name, _lastname, _phone), BaseEntity(_id) {}

void Client::addParIDptrList(sharedParObjPtr ptr)
{
	parIDptrList.push_back(ptr);
}

bool Client::matchTheRegex(string& str)
{
	regex search("\\w*" + str + "\\w*", regex_constants::icase);
	return regex_match(name, search) || regex_match(lastname, search) || regex_match(phoneNumber, search);
}

bool Client::readNumber(stringstream &ss)
{
	ss.clear();
	int iLiczba;
	ss >> iLiczba;
	if (ss.bad())
	{
		cout << "Hardware error while processing a number from stringstream." << endl;
		ss.clear();
		return false;
	}
	else
		if (ss.fail())
			return false;
		else
			parIDContainer.push_back(iLiczba);
	return true;
}

bool Client::readChar(stringstream & ss)
{
	ss.clear();
	char cZnak;
	ss >> cZnak;
	if (ss.bad())
	{
		cout << "Hardware error while processing a character from stringstream." << endl;
		ss.clear();
		return false;
	}
	else
		if (ss.fail())
			return false;

	return true;
}

bool Client::readSS(stringstream &ss)
{
	if (!ss.good())
	{
		std::cout << "Something's wrong with stringstream in readSS function." << std::endl;
		return false;
	}
	while (ss)
	{
		if (!readNumber(ss) && ss.bad())
			return false;
		else
			if (!readChar(ss))
			{
				if (ss.bad())
					return false;
				else
					break; //no more characters to read from the string
			}
	}
	ss.clear();
	return true;
}

//aktualizacja stringu parcels(gotowosc do zapisu do pliku)
void Client::setParcels()
{
	stringstream result;
	result << "[";
	for (auto i : parIDContainer)
	{
		result << i << ",";
	}
	result.seekp(-1, result.cur);
	result << "]";

	parcels = result.str();
}

string Client::getParcels()
{
	setParcels();
	return parcels;
}

//inicjalizowany w konstruktorze, przyjmuje odczytany z pliku string wyciagajac z niego liczby (id) i wsadza je w kontenerParID
void Client::setParIDContainer(string cliString)
{
	if (cliString.length() == 0)
		throw "Couldn't convert agreement's IDs of the vehicles. The string is empty.";
	else
	{
		stringstream ss;
		ss.str(cliString);
		if (!readSS(ss))
			throw "ReadSS returned false. Something's wrong.";
	}
}

ostream& operator<<(ostream& os, const Client& cli)
{
	os << "ID: " << cli.id;
	os << " Name: " << cli.name;
	os << " Lastname: " << cli.lastname;
	os << " Phone: " << cli.phoneNumber;
	return os;
}