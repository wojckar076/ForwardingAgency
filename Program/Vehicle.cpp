#include "Vehicle.h"

Vehicle::Vehicle(int idVeh, string mod, string plates, int cap, bool available) 
	: BaseEntity(idVeh), model(mod), plateNumber(plates), EUROcapacity(cap), isAvailable(available) {}

Vehicle::Vehicle(int idVeh, string mod, string plates, int cap)
	: BaseEntity(idVeh), model(mod), plateNumber(plates), EUROcapacity(cap) { isAvailable = 1; }

int Vehicle::getID() { return id; }
string Vehicle::getModel() { return model; }
string Vehicle::getPlates() { return plateNumber; }
int Vehicle::getCapacity() { return EUROcapacity; }
bool Vehicle::getAvailability() { return isAvailable; }

void Vehicle::changeAvailability() 
{ 
	this->isAvailable = !isAvailable; 
}

void Vehicle::setModel(string _model)
{
	model = _model;
}

void Vehicle::setPlates(string newPlates) 
{ 
	this->plateNumber = newPlates; 
}

void Vehicle::setEuroCap(int cap)
{
	EUROcapacity = cap;
}

void Vehicle::setAvailability()
{
	isAvailable = true;
}
