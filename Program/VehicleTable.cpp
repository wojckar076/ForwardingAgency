#include "VehicleTable.h"

VehicleTable::VehicleTable() 
{
	currentMaxID = 0;
	fstream vehicleFile("Vehicles.txt", ios::in);
	if (!vehicleFile.good())
	{
		throw "Something went wrong while loading the vehicle file.";
	}
	else
	{
		string singleLane;
		while (getline(vehicleFile, singleLane))
		{
			stringstream pom(singleLane);

			int vehID;
			pom >> vehID;

			if (vehID > currentMaxID)
				currentMaxID = vehID;

			string model;
			pom >> model;

			string plates;
			pom >> plates;

			int capacity;
			pom >> capacity;

			bool avail;
			pom >> avail;

			entityList.push_back(sharedVehObjPtr(new Vehicle(vehID, model, plates, capacity, avail)));
		}
	}
	vehicleFile.close();
}

VehicleTable::~VehicleTable()
{
	entityList.clear();
}


list<sharedVehObjPtr> VehicleTable::showRegexMatches(string pattern)
{
	list<sharedVehObjPtr> resultList;
	regex options(pattern, regex_constants::icase);
	list<sharedVehObjPtr> drawVehObjects = getAllVehicles();
	for (auto &i : drawVehObjects)
	{
		if (regex_match(i->getModel(), options)
			|| regex_match(i->getPlates(), options))
		{
			resultList.push_back(i);
		}
	}
	return resultList;
}

void VehicleTable::saveChangesToFile()
{
	fstream vehicleFile("Vehicles.txt", ios::out);
	if (!vehicleFile.good())
	{
		throw "Couldn't open the vehicle file.";
	}
	else
	{
		for (auto const& veh : entityList)
		{
			vehicleFile << veh->getID() << " " << veh->getModel() << " " << veh->getPlates() << " " << veh->getCapacity() << " " << veh->getAvailability() << endl;
		}
	}
	vehicleFile.close();
}

int VehicleTable::getIncrementedID() { return ++currentMaxID; }

list<sharedVehObjPtr> VehicleTable::getAllVehicles()
{
	return entityList;
}

ostream& operator<<(ostream& os, VehicleTable* vt)
{
	list<sharedVehObjPtr> vehlist = vt->getAllVehicles();
	list<sharedVehObjPtr>::iterator it;

	os << left << setw(4) << "ID"
	   << left << setw(15) << "Model"
	   << left << setw(10) << "Plates"
	   << left << setw(10) << "Capacity"
	   << "Availability" << endl;
	for (it = vehlist.begin(); it != vehlist.end(); ++it)
		os << left << setw(4) << (*it)->getID()
		   << left << setw(15) << (*it)->getModel()
		   << left << setw(10) << (*it)->getPlates()
		   << left << setw(10) << (*it)->getCapacity()
		   << (*it)->getAvailability() << endl;
	return os;
}