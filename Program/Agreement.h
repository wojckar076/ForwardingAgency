#pragma once
#define _CRT_SECURE_NO_WARNINGS //dla timenow

#include "CommonTypedefs.h"
#include "Vehicle.h"
#include "BaseEntity.h"
#include "Employee.h"
#include "Parcel.h"
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

class Agreement : BaseEntity{
	string dateOfSigning;
	int cliID;
	int empID;
	int parID;
	string vehIDs;

	sharedCliObjPtr cliIDptr;
	sharedEmpObjPtr empIDptr;
	sharedParObjPtr parIDptr; 
	list<int> vehIDContainer;
	list<sharedVehObjPtr> vehIDptrList;
	bool readNumber(stringstream &);
	bool readChar(stringstream &);
public:
	Agreement(int, int, int, string, string);
	int getID();
	int getCliID();
	int getEmpID();
	int getParID();
	string getDate();
	string getStringVehID();
	list<int> getVehIDContainer();
	sharedCliObjPtr getCliIDptr();
	sharedEmpObjPtr getEmpIDptr();
	sharedParObjPtr getParIDptr();
	void setDate();			//ustawia dzisiejsza date

	void setEmpPtr(sharedEmpObjPtr); // te settery przy tworzeniu umowy przyjmuja pointer na obiekt ktory uczestniczy w umowie
	void setParPtr(sharedParObjPtr); 
	void setCliPtr(sharedCliObjPtr );
	void addVehIDptr(sharedVehObjPtr);
	void setCliID(int);
	void setEmpID(int);
	void setParID();
	void setVehIDs(); //wykorzystywane przy zakladaniu umowy - liste pobranych id pojazdów (wybranych przez backpack)
					//po wczesniejszym przerobieniu (kodem z 3.34) na stringa przyjmuje obiekt Agreement i 
					// wsadza sobie stringa w postaci [1,2,3...], ktory nastepnie przekaze jako parametr 
					// konstruktorowi agreementu
	
	void setVehIDContainer(string); //przyjmuje string ajdików w postaci np. [1,2,3,7] 
						   //i je z niego wyci¹ga wsadzaj¹c w vec

	bool readSS(stringstream &);

	friend ostream& operator<<(ostream& os, sharedAgrObjPtr agr)
	{
		os << agr->getID() << "\t" << agr->parIDptr->getName() << "\t" << agr->empIDptr->getLogin() << "\t" << agr->getDate();
		return os;
	}
};