#pragma once
#include "CommonTypedefs.h"
#include "BaseEntity.h"
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>

using namespace std;

class Parcel : public BaseEntity {
private:
	string name;
	int volume;
	string destination;
	int ownerID;
	sharedCliObjPtr cliptr;

public:
	~Parcel();
	Parcel(int, string, int, string, int);

	int getID();
	string getName();
	int getVolume();
	string getDestination();
	int getOwnersID();
	sharedCliObjPtr getOwnerIDPtr();
	void setOwnerObj(sharedCliObjPtr);


	friend ostream& operator<<(ostream& os, const Parcel& par)
	{
		os << "ID: " << par.id << endl;
		os << "Name: " << par.name << endl;
		os << "Volume: " << par.volume << endl;
		os << "Destination: " << par.destination << endl;
		os << "Sent by client: " << par.ownerID << endl << endl;
		return os;
	}

};