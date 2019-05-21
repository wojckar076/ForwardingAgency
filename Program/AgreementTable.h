#pragma once
#include "Agreement.h"
#include "DBTable.h"

class AgreementTable : public DBTable<Agreement>
{
	int currentMaxID;

public:
	AgreementTable();
	~AgreementTable();
	int getIncrementedID();
	list<sharedAgrObjPtr> getAllAgreements();

	void saveChangesToFile();

	friend ostream& operator<<(ostream& os, AgreementTable* agr);
};