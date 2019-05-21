#include "Parcel.h"

Parcel::~Parcel() {}

Parcel::Parcel(int id, string name, int vol, string desti, int cliid) 
	: BaseEntity(id), name(name), volume(vol), destination(desti), ownerID(cliid) 
{
	cliptr = nullptr;
}

int Parcel::getID() { return id; }
string Parcel::getName() { return name; }
int Parcel::getVolume() { return volume; }
string Parcel::getDestination() { return destination; }
int Parcel::getOwnersID() { return ownerID; }

sharedCliObjPtr Parcel::getOwnerIDPtr()
{
	return cliptr;
}

void Parcel::setOwnerObj(sharedCliObjPtr ptr)
{
	this->cliptr = ptr;
}