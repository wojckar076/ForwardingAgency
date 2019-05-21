#pragma once
#include "Person.h"
#include "BaseEntity.h"
#include "CommonTypedefs.h"
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <regex>

class Client : public Person, public BaseEntity {
	string parcels;		
	list<int> parIDContainer;	    
	list<sharedParObjPtr> parIDptrList;

	bool readNumber(stringstream &);
	bool readChar(stringstream &);

public:
	Client() { parcels = ""; }
	~Client() {}
	Client(int, string, string, string, string);
	Client(int, string, string, string);

	bool matchTheRegex(string&);
	string getParcels();
	int getID() { return id; }
	list<int> getParIDContainer() { return parIDContainer; }
	void addParIDptrList(sharedParObjPtr);
	bool readSS(stringstream &);
	void setParcels();
	void setParIDContainer(string);
		
	friend ostream& operator<<(ostream& os, const Client& cli);
};