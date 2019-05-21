#include "EmployeeTable.h"

EmployeeTable::EmployeeTable()
{
	currentMaxID = 0;
	fstream clientFile("Employees.txt", ios::in);
	if (!clientFile.good())
	{
		throw "Something went wrong while loading the employee file.";
	}
	else
	{
		string singleLane;
		while (getline(clientFile, singleLane))
		{
			stringstream pom(singleLane);

			int empID;
			pom >> empID;

			if (empID > currentMaxID)
				currentMaxID = empID;

			string name;
			pom >> name;

			string lastname;
			pom >> lastname;

			string phone;
			pom >> phone;

			string login;
			pom >> login;

			string pass;
			pom >> pass;

			entityList.push_back(sharedEmpObjPtr(new Employee(empID, name, lastname, phone, login, pass)));
		}
	}
	clientFile.close();
}

EmployeeTable::~EmployeeTable()
{
	entityList.clear();
}

void EmployeeTable::saveChangesToFile()
{
	fstream employeeFile("Employees.txt", ios::out);
	if (!employeeFile.good())
	{
		throw "Couldn't open the employee file.";
	}
	else
	{
		for (auto const &emp : this->getAllEmployees())
		{
			employeeFile << emp->getID() << " " << emp->getName() << " " << emp->getLastname() << " " << emp->getPhoneNumber() << " " << emp->getLogin() << " " << emp->getPassword() << endl;
		}
	}
	employeeFile.close();	
}

list<sharedEmpObjPtr> EmployeeTable::showRegexMatches(string pattern)
{
	list<sharedEmpObjPtr> resultList;
	regex options(pattern, regex_constants::icase);
	list<sharedEmpObjPtr> drawEmpObjects = getAllEmployees();
	for (auto &i : drawEmpObjects)
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

list<sharedEmpObjPtr> EmployeeTable::getAllEmployees() { return entityList; }

int EmployeeTable::getMaxID() { return currentMaxID; }

int EmployeeTable::getIncrementedID() { return ++currentMaxID; }

ostream& operator<<(ostream& os, EmployeeTable* vt)
{
	list<sharedEmpObjPtr> empList = vt->getAllEmployees();
	list<sharedEmpObjPtr>::iterator it;

	os << left << setw(4) << "ID"
		<< left << setw(15) << "Name"
		<< left << setw(10) << "Lastname"
		<< left << setw(10) << "Phone" << endl;
	for (it = empList.begin(); it != empList.end(); ++it)
		os << left << setw(4) << (*it)->getID()
		<< left << setw(15) << (*it)->getName()
		<< left << setw(10) << (*it)->getLastname()
		<< left << setw(10) << (*it)->getPhoneNumber() << endl;
	return os;
}