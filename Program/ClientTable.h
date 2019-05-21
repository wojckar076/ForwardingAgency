#pragma once
#include "Client.h"
#include "DBTable.h"
#include <iomanip>
#include <vector>

class ClientTable : public DBTable<Client>
{
	int currentMaxID;

public:
	ClientTable();
	~ClientTable();
	list<sharedCliObjPtr> showRegexMatches(string pattern);
	int getMaxID();
	int getIncrementedID();
	list<sharedCliObjPtr> getAllClients();

	void saveChangesToFile();

	friend ostream& operator<<(ostream& os, ClientTable* cli);
};