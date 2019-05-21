#pragma once

#include "Database.h"
#include "Backpack.h"

typedef shared_ptr<Database> DBsharedPtr;
class Interface {
	DBsharedPtr db;
	bool isLogged;
	int activeEmpID;
	int activeClientID = 0;
public:
	Interface();
	~Interface();

	DBsharedPtr getDB();

	void refreshDatabase();

	void run();
	void shutDown();

	bool getIsLogged();
	void displayLoginScreen();
	
	void displaySearchOption();
	void displayRegexClientSearch();
	void displayRegexEmployeeSearch();
	void displayRegexVehicleSearch();

	void displayAllTables();

	void displayAgreementRemoval();
	void displayClientRemoval();
	void displayEmployeeRemoval();
	void displayParcelRemoval();
	void displayVehicleRemoval();
	void displayClientParcels();

	void displayEditPlateNumber();
	void displayEditPassword();

	void displayAddNewAgreement();
	void displayAddNewEmployee();
	void displayAddNewVehicle();

	void displayMainMenu();

};