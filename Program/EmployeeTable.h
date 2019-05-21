#pragma once
#include "Employee.h"
#include "DBTable.h"

class EmployeeTable : public DBTable<Employee>
{
	int currentMaxID;

public:
	EmployeeTable();
	~EmployeeTable();
	int getMaxID();
	int getIncrementedID();
	list<sharedEmpObjPtr> getAllEmployees();
	list<sharedEmpObjPtr> showRegexMatches(string );

	void saveChangesToFile();

	friend ostream& operator<<(ostream& os, EmployeeTable* emp);
};
