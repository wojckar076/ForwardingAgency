#pragma once
#include "Vehicle.h"
#include "DBTable.h"
#include <iomanip>

class VehicleTable : public DBTable<Vehicle> 
{
	int currentMaxID;
public:
	VehicleTable();
	~VehicleTable();
	int getIncrementedID();
	list<sharedVehObjPtr> getAllVehicles();
	list<sharedVehObjPtr> showRegexMatches(string);

	void saveChangesToFile();

	friend ostream& operator<<(ostream& os, VehicleTable* vt);
};