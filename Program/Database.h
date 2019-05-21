#pragma once
#include "AgreementTable.h"
#include "ClientTable.h"
#include "EmployeeTable.h"
#include "ParcelTable.h"
#include "VehicleTable.h"
#include "Backpack.h"
#include <string>
#include <memory>

using namespace std;

typedef shared_ptr<ClientTable> CliTablePtr;
typedef shared_ptr<EmployeeTable> EmpTablePtr;
typedef shared_ptr<VehicleTable> VehTablePtr;
typedef shared_ptr<ParcelTable> ParTablePtr;
typedef shared_ptr<AgreementTable> AgrTablePtr;

template<typename T>
void showTable(shared_ptr<T> table)
{
	cout << table << endl;
}

class Database {
private:
	CliTablePtr cliTable;
	EmpTablePtr empTable;
	VehTablePtr vehTable;
	ParTablePtr parTable;
	AgrTablePtr agrTable;

public:
	Database();
	~Database();
	CliTablePtr getCliTable();
	EmpTablePtr getEmpTable();
	VehTablePtr getVehTable();
	ParTablePtr getParTable();
	AgrTablePtr getAgrTable();
	string getToday();

	void linkCliParTables();
	void linkAgrTableWithOthers();
	void addNewParcel(sharedParObjPtr parPtr){  }

	bool regexSearchClient(string);
	bool regexSearchEmployee(string);
	bool regexSearchVehicle(string);
	bool regexSearchAgreement(string);
	bool regexSearchParcel(string);
	bool checkPassword(string, int);
	bool changePassword(string, int);

	list<sharedVehObjPtr> getVehiclesForTheTransport(int );
	string getVehiclesAsString(list<sharedVehObjPtr>);

	void searchForClientsParcels(int );
};