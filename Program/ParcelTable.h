#pragma once
#include "Parcel.h"
#include "DBTable.h"

class ParcelTable : public DBTable<Parcel>
{
	int currentMaxID;
public:
	ParcelTable();
	~ParcelTable();
	int getMaxID();
	int getIncrementedID();
	list<sharedParObjPtr> getAllParcels();

	void addNewParcel(sharedParObjPtr);
	void removeParcel(int);
	void saveChangesToFile();

	friend ostream& operator<<(ostream& os, ParcelTable* par);
};
