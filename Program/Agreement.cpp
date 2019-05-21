#include "Agreement.h"

Agreement::Agreement(int _id, int cid, int eid, string vids, string date)
		: BaseEntity(_id), cliID(cid), empID(eid), vehIDs(vids), dateOfSigning(date), parID(_id)
{
	try
	{
		this->setVehIDContainer(vids);
	}
	catch (const char* ex) {
		cout << ex << endl;
	}
	
	this->empIDptr = nullptr;
	this->parIDptr = nullptr;

}

void Agreement::setDate()
{
	struct tm  tstruct;
	time_t now = time(NULL);   // get time now
	tm* tmptr = localtime(&now);
	stringstream ss;
	ss << (tmptr->tm_year + 1900) << '-'
		<< (tmptr->tm_mon + 1) << '-'
		<< tmptr->tm_mday;
	dateOfSigning = ss.str();
}

int Agreement::getID() { return id; }
int Agreement::getCliID() { return cliID; }
int Agreement::getEmpID() { return empID; }
int Agreement::getParID() { return parID; }
string Agreement::getDate() { return dateOfSigning; }
string Agreement::getStringVehID() { return vehIDs; }
void Agreement::setCliID(int cliid) { cliID = cliid; } //sharedCliObjPtr ptr->getId() przekazac w parametrze przy wywolaniu
void Agreement::setEmpID(int empid) { empID = empid; } //sharedEmpObjPtr ptr->getId() przekazac w parametrze przy wywolaniu
void Agreement::setParID() { parID = id; } //sharedParObjPtr ptr->getId() przekazac w parametrze przy wywolaniu

list<int> Agreement::getVehIDContainer()
{
	return vehIDContainer;
}

sharedCliObjPtr Agreement::getCliIDptr() { return cliIDptr; }
sharedEmpObjPtr Agreement::getEmpIDptr() { return empIDptr; }
sharedParObjPtr Agreement::getParIDptr() { return parIDptr; }

void Agreement::addVehIDptr(sharedVehObjPtr ptr)
{
	vehIDptrList.push_back(ptr);
}



void Agreement::setEmpPtr(sharedEmpObjPtr ptr)
{
	this->empIDptr = ptr;
}

void Agreement::setParPtr(sharedParObjPtr ptr)
{
	this->parIDptr = ptr;
}

void Agreement::setCliPtr(sharedCliObjPtr ptr)
{
	this->cliIDptr = ptr;
}

bool Agreement::readNumber(stringstream &ss)
{
	ss.clear();
	int iLiczba;
	ss >> iLiczba;
	if (ss.bad())
	{
		ss.clear();
		return false;
	}
	else
		if (ss.fail())
			return false;
		else
			vehIDContainer.push_back(iLiczba);
	return true;
}

bool Agreement::readChar(stringstream & ss)
{
	ss.clear();
	char cZnak;
	ss >> cZnak;
	if (ss.bad())
	{
		ss.clear();
		return false;
	}
	else
		if (ss.fail())
			return false;

	return true;
}

bool Agreement::readSS(stringstream &ss)
{
	if (!ss.good())
	{
		std::cout << "Something's wrong with stringstream in readSS function." << std::endl;
		return false;
	}
	while (ss)
	{
		if (!readNumber(ss) && ss.bad())
			return false;
		else
			if (!readChar(ss))
			{
				if (ss.bad())
					return false;
				else
					break; //no more characters to read from the string
			}
	}
	ss.clear();
	return true;
}

void Agreement::setVehIDContainer(string vehString)
{
	if (vehString.length() == 0)
		throw "Couldn't convert agreement's IDs of the vehicles. The string is empty.";
	else
	{
		stringstream ss;
		ss.str(vehString);
		if (!readSS(ss))
			throw "ReadSS returned false. Something's wrong.";
	}
}