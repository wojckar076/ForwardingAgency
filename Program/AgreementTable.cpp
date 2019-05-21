#include "AgreementTable.h"

AgreementTable::AgreementTable() 
{
	currentMaxID = 0;
	fstream agreementFile("Agreements.txt", ios::in);
	if (!agreementFile.good())
	{
		throw "Something went wrong while loading the agreements file.";
	}
	else
	{
		string singleLane;
		while (getline(agreementFile, singleLane))
		{
			stringstream pom(singleLane);

			int agrID;
			pom >> agrID;

			if (agrID > currentMaxID)
				currentMaxID = agrID;

			int parID;
			pom >> parID;

			int empID;
			pom >> empID;

			string date;
			pom >> date;

			string vehiclesID;
			pom >> vehiclesID;

			entityList.push_back(sharedAgrObjPtr(new Agreement(agrID, parID, empID, date, vehiclesID)));
		}
	}
	agreementFile.close();
}

AgreementTable::~AgreementTable() 
{
	entityList.clear();
}

void AgreementTable::saveChangesToFile()
{
	fstream agreementFile("Agreements.txt", ios::out);
	if (!agreementFile.good())
	{
		throw "Couldn't save the agreements file.";
	}
	else
	{
		for (auto const& agr : entityList)
		{
			agreementFile << agr->getID() << " " << agr->getCliID() << " " << agr->getEmpID() << " " << agr->getStringVehID() << " " << agr->getDate() << endl;
		}
	}
	agreementFile.close();
}

int AgreementTable::getIncrementedID() { return ++currentMaxID; }

list<sharedAgrObjPtr> AgreementTable::getAllAgreements()
{
	return entityList;
}

ostream& operator<<(ostream& os, AgreementTable* par)
{
	list<sharedAgrObjPtr> agrlist = par->getAllAgreements();
	list<sharedAgrObjPtr>::iterator it;

	os << left << setw(4)		<< "ID"
		<< left << setw(15) << "Parcel's Name"
		<< left << setw(20) << "Emplyoee"
		<< left << setw(15) << "Signed on" << endl;
	for (auto i : agrlist)
		os << i << endl;
	return os;
}