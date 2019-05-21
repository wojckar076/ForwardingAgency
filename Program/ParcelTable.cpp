#include "ParcelTable.h"

ParcelTable::ParcelTable() 
{
	currentMaxID = 0;
	fstream parcelFile("Parcels.txt", ios::in);
	if (!parcelFile.good())
	{
		throw "Something went wrong while loading the parcel file.";
	}
	else
	{
		string singleLane;
		while (getline(parcelFile, singleLane))
		{
			stringstream pom(singleLane);

			int parID;
			pom >> parID;

			if (parID > currentMaxID)
				currentMaxID = parID;

			string name;
			pom >> name;

			int vol;
			pom >> vol;

			string dest;
			pom >> dest;

			int cliID;
			pom >> cliID;

			entityList.push_back(sharedParObjPtr(new Parcel(parID, name, vol, dest, cliID)));
		}
	}
	parcelFile.close();
}

ParcelTable::~ParcelTable()
{
	entityList.clear();
}

void ParcelTable::saveChangesToFile()
{
	fstream parcelFile("Parcels.txt", ios::out);
	if (!parcelFile.good())
	{
		throw "Couldn't open the parcel file.";
	}
	else
	{
		for (auto const &par : this->getAllParcels())
		{
			parcelFile << par->getID() << " " << par->getName() << " " << par->getVolume() << " " << par->getDestination() << " " << par->getOwnersID() << endl;
		}
	}
	parcelFile.close();	
}

int ParcelTable::getMaxID() { return currentMaxID; }

int ParcelTable::getIncrementedID() { return ++currentMaxID; }

list<sharedParObjPtr> ParcelTable::getAllParcels() { return entityList; }

void ParcelTable::addNewParcel(sharedParObjPtr par)
{
	entityList.push_back(par);
}

void ParcelTable::removeParcel(int id)
{
	for (list<sharedParObjPtr>::iterator it = entityList.begin(); it != entityList.end(); ++it)
	{
		if ((*it)->getID() == id)
		{
			entityList.erase(it);
			break;
		}
	}
}

ostream& operator<<(ostream& os, ParcelTable* vt)
{
	list<sharedParObjPtr> parlist = vt->getAllParcels();
	list<sharedParObjPtr>::iterator it;

	os << left << setw(4) << "ID"
		<< left << setw(15) << "Name"
		<< left << setw(10) << "Volume"
		<< left << setw(14) << "Destination" 
		<< left << setw(4)  << "Owner's ID" << endl;
	for (it = parlist.begin(); it != parlist.end(); ++it)
		os << left << setw(4) << (*it)->getID()
		<< left << setw(15) << (*it)->getName()
		<< left << setw(10) << (*it)->getVolume()
		<< left << setw(14) << (*it)->getDestination()
		<< left << setw(4) << (*it)-> getOwnersID() << endl;
	return os;
}