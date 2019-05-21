#include "Database.h"

Database::Database() {
	try
	{
		vehTable = VehTablePtr(new VehicleTable());
		empTable = EmpTablePtr(new EmployeeTable());
		cliTable = CliTablePtr(new ClientTable());
		parTable = ParTablePtr(new ParcelTable());
		agrTable = AgrTablePtr(new AgreementTable());

	}
	catch (const char* ex) {
		cout << ex << endl;
		cout << "It is advised to exit the program and check if data files are present in program's folder." << endl;
	}
}

Database::~Database() {}

CliTablePtr Database::getCliTable() { return cliTable; }
EmpTablePtr Database::getEmpTable() { return empTable; }
VehTablePtr Database::getVehTable() { return vehTable; }
ParTablePtr Database::getParTable() { return parTable; }
AgrTablePtr Database::getAgrTable() { return agrTable; }

list<sharedVehObjPtr> Database::getVehiclesForTheTransport(int vol)
{
	Backpack backpack;

	list<sharedVehObjPtr> availableVehicles = backpack.getAvailableVehicles(getVehTable()->getAllVehicles());
	if (!backpack.computeBackpack(availableVehicles, vol))
	{
		throw "There's not enough vehicles to send this parcel.";
	}

	return backpack.getBackpackList();
}

string Database::getVehiclesAsString(list<sharedVehObjPtr> backpackVehicles)
{
	stringstream result;
	result << "[";
	for (auto i : backpackVehicles)
	{
		result << i->getID() << ",";
	}
	result.seekg(0, ios::end);
	int size = result.tellg();
	result.seekg(0, ios::beg);
	if (size > 2)
	{
		result.seekp(-1, result.cur);
		result << "]";
		return result.str();
	}
	else return "[]";
}

bool Database::checkPassword(string p, int activeID)
{
	for (auto i : empTable->getAllEmployees())
	{
		if (i->getID() == activeID)
		{
			if (i->getPassword() == p)
				return true;
			else return false;
		}
	}
	throw "Found no employees with such ID, are you really our employee?";
}
bool Database::changePassword(string newP, int activeID)
{
	for (auto i : empTable->getAllEmployees())
	{
		if (i->getID() == activeID)
		{
			i->setPassword(newP);
			return true;
		}
	}
	return false;
}

void Database::searchForClientsParcels(int idcli)
{
	list<sharedParObjPtr> specificClientsParcels;
	for (auto &par : parTable->getAllParcels())
	{
		if (par->getOwnersID() == idcli)
			specificClientsParcels.push_back(par);
	}
	for (auto &out : specificClientsParcels)
		cout << (*out) << endl;
	getchar();
}

string Database::getToday()
{
	struct tm  tstruct;
	time_t now = time(NULL);   // get time now
	tm* tmptr = localtime(&now);
	stringstream ss;
	ss << (tmptr->tm_year + 1900) << '-'
		<< (tmptr->tm_mon + 1) << '-'
		<< tmptr->tm_mday;
	return ss.str();
}

void Database::linkCliParTables()
{
	list<sharedCliObjPtr>::iterator itCli;
	list<sharedParObjPtr>::iterator itPar;

	list<sharedCliObjPtr> clilist = cliTable->getAllClients();
	list<sharedParObjPtr> parlist = parTable->getAllParcels();
	for (itCli = clilist.begin(); itCli != clilist.end(); ++itCli)
	{
		list<int> parids = (*itCli)->getParIDContainer();
		int count = 0;
		for (itPar = parlist.begin(); itPar != parlist.end(); ++itPar)
		{
			for (auto p : parids)
			{
				if (p == (*itPar)->getOwnersID())
				{
					(*itCli)->addParIDptrList(*itPar);
					(*itPar)->setOwnerObj(*itCli);
					count++;
					break;
				}
			}
			if (count == parids.size())
				break;
		}
	}
}

void Database::linkAgrTableWithOthers()
{
	list<sharedVehObjPtr> vehlist = vehTable->getAllVehicles();
	list<sharedVehObjPtr>::iterator itVeh;
	list<sharedEmpObjPtr> emplist = empTable->getAllEmployees();
	list<sharedEmpObjPtr>::iterator itEmp;
	list<sharedParObjPtr> parlist = parTable->getAllParcels();
	list<sharedParObjPtr>::iterator itPar;
	list<sharedAgrObjPtr> agrlist = agrTable->getAllAgreements();
	list<sharedAgrObjPtr>::iterator itAgr;
	for (itAgr = agrlist.begin(); itAgr != agrlist.end(); ++itAgr)
	{
		list<int> vehids = (*itAgr)->getVehIDContainer();
		int count = 0;
		for (itVeh = vehlist.begin(); itVeh != vehlist.end(); ++itVeh)
		{
			for (auto a : vehids)
			{
				if (a == (*itVeh)->getID())
				{
					(*itAgr)->addVehIDptr(*itVeh);
					count++;
					break;
				}
			}
			if (count == vehids.size())
				break;
		}
		for (itEmp = emplist.begin(); itEmp != emplist.end(); ++itEmp)
		{
			if ((*itEmp)->getID() == (*itAgr)->getEmpID())
			{
				(*itAgr)->setEmpPtr(*itEmp);
				break;
			}
		}

		for (itPar = parlist.begin(); itPar != parlist.end(); ++itPar)
		{
			if ((*itPar)->getID() == (*itAgr)->getParID())
			{
				(*itAgr)->setParPtr(*itPar);
				(*itAgr)->setCliPtr((*itPar)->getOwnerIDPtr());
				break;
			}
		}
	}
}

///UZYCIE REGEXA DLA KLIENTA
bool Database::regexSearchClient(string pattern)
{

	CliTablePtr table = getCliTable();
	list<sharedCliObjPtr> regexList = table->showRegexMatches(pattern);
	for (auto i : regexList)
	{
		cout << (*i) << endl;
	}
	if (regexList.size() == 0)
		return false;
	else return true;
}

bool Database::regexSearchEmployee(string pattern)
{
	EmpTablePtr table = getEmpTable();
	list<sharedEmpObjPtr> regexList = table->showRegexMatches(pattern);
	for (auto i : regexList)
	{
		cout << (*i) << endl;
	}
	if (regexList.size() == 0)
		return false;
	else return true;
}

bool Database::regexSearchVehicle(string pattern)
{
	VehTablePtr table = getVehTable();
	list<sharedVehObjPtr> regexList = table->showRegexMatches(pattern);
	for (auto i : regexList)
	{
		cout << (*i) << endl;
	}
	if (regexList.size() == 0)
		return false;
	else return true;
}