#pragma once
#include "CommonTypedefs.h"
#include "BaseEntity.h"
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

using namespace std;

class Vehicle : public BaseEntity {
	string model;
	string plateNumber;
	int EUROcapacity;
	bool isAvailable;
public:
	Vehicle(int, string, string, int, bool);
	Vehicle(int, string, string, int);

	//getters
	int getID();
	string getModel();
	string getPlates();
	int getCapacity();
	bool getAvailability();
	//setters
	void changeAvailability();
	void setModel(string);
	void setPlates(string);
	void setEuroCap(int);
	void setAvailability();

	friend ostream& operator<<(ostream& os, const Vehicle& veh)
	{
		os << "ID: " << veh.id << endl;
		os << "Model: " << veh.model << endl;
		os << "Plates: " << veh.plateNumber << endl;
		os << "Capacity:" << veh.EUROcapacity << endl;
		os << "Availability: " << veh.isAvailable << endl << endl;
		return os;
	}
};