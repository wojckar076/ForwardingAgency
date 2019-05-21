#include "ClientTable.h"

ClientTable::ClientTable()
{
	currentMaxID = 0;
	fstream clientFile("Clients.txt", ios::in);
	if (!clientFile.good())
	{
		throw "Something went wrong while loading the client file.";
	}
	else
	{
		string singleLane;
		while (getline(clientFile, singleLane))
		{
			stringstream pom(singleLane);

			int cliID;
			pom >> cliID;

			if (cliID > currentMaxID)
				currentMaxID = cliID;

			string name;
			pom >> name;

			string lastname;
			pom >> lastname;

			string phone;
			pom >> phone;

			string parcels;
			pom >> parcels;

			entityList.push_back(sharedCliObjPtr(new Client(cliID, name, lastname, phone, parcels)));
		}
	}
	clientFile.close();
}

ClientTable::~ClientTable()
{
	entityList.clear();
}

void ClientTable::saveChangesToFile()
{
	fstream clientFile("Clients.txt", ios::out);
	if (!clientFile.good())
	{
		throw "Couldn't open the client file.";
	}
	else
	{
		for (auto const& cli : this->getAllClients())
			clientFile << cli->getID() << " " << cli->getName() << " " << cli->getLastname() << " " << cli->getPhoneNumber() << " " << cli->getParcels() << endl;
	}
	clientFile.close();
}

list<sharedCliObjPtr> ClientTable::showRegexMatches(string pattern)
{
	list<sharedCliObjPtr> resultList;
	regex options(pattern, regex_constants::icase);
	list<sharedCliObjPtr> drawCliObjects = getAllClients();
	for (auto &i : drawCliObjects)
	{
		if (regex_match(i->getName(), options)
			|| regex_match(i->getLastname(), options)
			|| regex_match(i->getPhoneNumber(), options))
		{
			resultList.push_back(i);
		}
	}
	return resultList;
}

int ClientTable::getMaxID() { return currentMaxID; }

int ClientTable::getIncrementedID() { return ++currentMaxID; }

list<sharedCliObjPtr> ClientTable::getAllClients() { return entityList; }

ostream& operator<<(ostream& os, ClientTable* cli)
{
	list<sharedCliObjPtr> clilist = cli->getAllClients();
	list<sharedCliObjPtr>::iterator it;

	os << left << setw(4) << "ID"
		<< left << setw(12) << "Name"
		<< left << setw(15) << "Last name"
		<< left << setw(10) << "Phone nr" << endl;
	for (it = clilist.begin(); it != clilist.end(); ++it)
		os << left << setw(4) << (*it)->getID()
		<< left << setw(12) << (*it)->getName()
		<< left << setw(15) << (*it)->getLastname()
		<< left << setw(10) << (*it)->getPhoneNumber() << endl;
	return os;
}
