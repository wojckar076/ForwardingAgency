#pragma once
#include "CommonTypedefs.h"
#include "Vehicle.h"
#include <iostream>
#include <list>

#define EURO4 4
#define EURO12 12
#define EURO24 24

//backpack is used while creating new agreement; takes in the amount of europalettes and gets list of available vehicles to 
//compute the best solution for transporting the parcel
class Backpack
{	
private:
	list<sharedVehObjPtr> backpackVehicles;
	string backpackVehString;
public:
	Backpack();
	~Backpack();
	list<sharedVehObjPtr> getBackpackList();
	list<sharedVehObjPtr> getAvailableVehicles(list<sharedVehObjPtr>);
	string setStringVehIDs();
	bool computeBackpack(list<sharedVehObjPtr> vehlist, int);					 
};