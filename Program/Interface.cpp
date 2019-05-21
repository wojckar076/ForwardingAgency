#include "Interface.h"

Interface::Interface()
{
	db = DBsharedPtr(new(Database));
	isLogged = false;
}

Interface::~Interface()
{
	isLogged = false;
}
DBsharedPtr Interface::getDB() { return db; }

bool Interface::getIsLogged()
{
	return isLogged;
}

void Interface::refreshDatabase()
{
	db->linkCliParTables();
	db->linkAgrTableWithOthers();
}


void Interface::displayLoginScreen()
{
	string login, pass;

	cout << "Please login using your credentials." << endl;
	cout << "Login: ";
	cin >> login;
	cout << "Password: ";
	cin >> pass;
	list<sharedEmpObjPtr> empPtrList = db->getEmpTable()->getAllEmployees();
	for (list<sharedEmpObjPtr>::iterator it = empPtrList.begin(); it != empPtrList.end(); ++it)
	{
		if ((*it)->getLogin() == login && (*it)->getPassword() == pass)
		{
			isLogged = true;
			activeEmpID = ((*it)->getID());
			break;
		}
	}
	system("cls");
}

void Interface::displayAllTables()
{
	showTable(db->getCliTable());
	showTable(db->getParTable());
	showTable(db->getVehTable());
	showTable(db->getEmpTable());
	showTable(db->getAgrTable());
	getchar();
}

void Interface::displayClientParcels()
{
	system("cls");
	showTable(db->getCliTable());
	int cliid;
	cout << "Which client's sent parcels would you like to see?" << endl;
	cout << "Type client's ID: ";
	cin >> cliid;
	system("cls");
	if (cliid > db->getCliTable()->getAllClients().size())
		cout << "There's no client with such ID." << endl;
	else {
		db->searchForClientsParcels(cliid);
	}
	getchar();
}

void Interface::displaySearchOption()
{

	int choice;
	cout << "Search for:" << endl
		<< "1. Clients" << endl
		<< "2. Employees" << endl
		<< "3. Vehicles" << endl
		<< "4. Client's Parcels" << endl;
	do
	{
		cin >> choice;

	} while (choice < 1 || choice>4);
	string keyWord;
	system("cls");
	switch (choice)
	{
	case 1:
		displayRegexClientSearch();
		break;
	case 2:
		displayRegexEmployeeSearch();
		break;
	case 3:
		displayRegexVehicleSearch();
		break;
	case 4: 
		displayClientParcels();
		break;
	default:
		break;
	}
	getchar();
}

void Interface::displayRegexClientSearch()
{
	string keyword;
	cout << "Client search using regex" << endl;
	cout << "Type the keyword: " << endl;
	cin >> keyword;
	if (!db->regexSearchClient(keyword))
	{
		system("cls");
		cout << "No words including " << keyword << " were found." << endl;
		cout << "Press any key to continue...";
	}
	getchar();
}

void Interface::displayRegexEmployeeSearch()
{
	string keyword;
	cout << "Employee search using regex" << endl;
	cout << "Type the keyword: " << endl;
	cin >> keyword;
	if (!db->regexSearchEmployee(keyword))
	{
		system("cls");
		cout << "No words including " << keyword << " were found." << endl;
		cout << "Press any key to continue...";
	}
	getchar();

}

void Interface::displayRegexVehicleSearch()
{
	string keyword;
	cout << "Vehicle search using regex" << endl;
	cout << "Type the keyword: " << endl;
	cin >> keyword;
	if (!db->regexSearchVehicle(keyword))
	{
		system("cls");
		cout << "No vehicles including " << keyword << " were found." << endl;
		cout << "Press any key to continue...";
	}
	getchar();
}



void Interface::displayAgreementRemoval()
{
	int i;
	cout << "Enter ID of the agreement you want to delete: ";
	cin >> i;
	if (i > db->getAgrTable()->getAllAgreements().size())
		cout << "There is no agreement with such ID." << endl;
	else {
		db->getAgrTable()->RemoveElementById(i);
		db->getAgrTable()->saveChangesToFile();
	}
}

void Interface::displayClientRemoval()
{
	int i;
	cout << "Enter ID of the client you want to delete: ";
	cin >> i;
	if (i > db->getCliTable()->getAllClients().size())
		cout << "There is no client with such ID." << endl;
	else {
		db->getCliTable()->RemoveElementById(i);
		db->getCliTable()->saveChangesToFile();
	}
}

void Interface::displayEmployeeRemoval()
{
	int i;
	cout << "Enter ID of the employee you want to delete: ";
	cin >> i;
	if (i > db->getEmpTable()->getAllEmployees().size())
		cout << "There is no employee with such ID." << endl;
	else {
		db->getEmpTable()->RemoveElementById(i);
		db->getEmpTable()->saveChangesToFile();
	}
}

void Interface::displayParcelRemoval()
{
	int i;
	cout << "Enter ID of the parcel you want to delete: ";
	cin >> i;
	if (i > db->getParTable()->getAllParcels().size())
		cout << "There is no employee with such ID." << endl;
	else {
		db->getParTable()->RemoveElementById(i);
		db->getParTable()->saveChangesToFile();
	}
}

void Interface::displayVehicleRemoval()
{
	int i;
	cout << "Enter ID of the vehicle you want to delete: ";
	cin >> i;
	if (i > db->getVehTable()->getAllVehicles().size())
		cout << "There is no employee with such ID." << endl;
	else {
		db->getVehTable()->RemoveElementById(i);
		db->getVehTable()->saveChangesToFile();
	}
}

void Interface::displayEditPlateNumber()
{
	list<sharedVehObjPtr> vehl = db->getVehTable()->getAllVehicles();

	int reg;
	cout << "Enter ID of the vehicle you would like to edit: ";
	cin >> reg;
	for (auto &veh : vehl)
	{
		if (veh->getID() == reg)
		{
			string newplates;
			do
			{
				cout << "\nEnter new plate numbers: ";
				cin >> newplates;
				if (newplates.length() > 7)
					cout << "New plate number appears to be too long." << endl;
			} while (newplates.length() > 7);
			string oldplates = veh->getPlates();
			veh->setPlates(newplates);
			cout << "Vehicles " << veh->getModel() << " plate number " << oldplates << " is now changed to " << newplates << endl;
			db->getVehTable()->saveChangesToFile();
		}
		if (veh->getID() > db->getVehTable()->getAllVehicles().size())
			cout << "It appears there's no vehicle with this ID." << endl;
	}
	getchar();
}

void Interface::displayEditPassword()
{
	string pass;
	cout << "Password change" << endl;
	cout << "In order to change the password you have to type your current password: ";
	cin >> pass;
	if (db->checkPassword(pass, activeEmpID))
	{
		string newpass;
		cout << "Type in new password: ";
		cin >> newpass;
		if (db->changePassword(newpass, activeEmpID))
		{
			db->getEmpTable()->saveChangesToFile();
			cout << "Password changed." << endl;

		}
		else cout << "Something wrong happened during password changing." << endl;
	}
	else
		cout << "You have typed wrong current password." << endl;

}

void Interface::displayAddNewAgreement()
{
	system("cls");
	cout << "Making new agreement" << endl;
	cout << "Do you want to create new client or choose existing from the database?\n";
	cout << "1. Create new client." << endl;
	cout << "2. Choose from database. " << endl;
	int *choice = new(int);
	do
	{
		cin >> *choice;
	} while (*choice < 0 || *choice > 2);

	switch (*choice)
	{
	case 0: 
	{
		cout << "Back to the menu." << endl;
		return;
	}
	case 1:
	{
		system("cls");
		string firstName, lastName, phone;

		cout << "Adding new client to database." << endl;
		int incrementedID = db->getCliTable()->getIncrementedID();
		cout << "Enter client's first name: ";
		cin >> firstName;
		cout << "Enter client's last name: ";
		cin >> lastName;
		cout << "Enter clien't phone number: ";
		cin >> phone;

		db->getCliTable()->AddToList(sharedCliObjPtr(new Client(incrementedID, firstName, lastName, phone)));
		activeClientID = incrementedID;
		break;
	}
	case 2:
	{
		system("cls");
		int idcli;

		showTable(db->getCliTable());
		cout << "Choose the client: ";
		cin >> idcli;
		if (idcli > db->getCliTable()->getAllClients().size())
		{
			cout << "It appears there's no client with this ID." << endl;
		}
		else
		{
			cout << "You chose client with id: " << idcli;
			activeClientID = idcli;
		}
		break;
	}
	default: break;
	}

	if (activeClientID != 0)
	{
		system("cls");
		string parName;
		string destination;
		int vol;
		cout << "Preparing the parcel" << endl;
		cout << "Type the name of the parcel: ";
		cin >> parName;
		cout << "\nWhat is the destination? ";
		cin >> destination;
		cout << "\nHow many palettes does it need for the transport? ";
		cin >> vol;

		sharedParObjPtr parPtr = sharedParObjPtr(new Parcel(db->getParTable()->getIncrementedID(), parName, vol, destination, activeClientID));
		db->getParTable()->AddToList(parPtr);
		db->getParTable()->saveChangesToFile();
		try
		{
			cout << "Preparing the agreement" << endl;
			list<sharedVehObjPtr> transportBy = db->getVehiclesForTheTransport(vol);
			string vehIds = db->getVehiclesAsString(transportBy);

			sharedAgrObjPtr agrPtr = sharedAgrObjPtr(new Agreement(db->getAgrTable()->getIncrementedID(), activeClientID, activeEmpID, vehIds, db->getToday()));
			for (auto v : transportBy)
			{
				v->changeAvailability();
			}
			refreshDatabase();
			db->getAgrTable()->AddToList(agrPtr);
			db->getAgrTable()->saveChangesToFile();

			cout << "Agreement created successfully." << endl;
			cout << "Transport by:" << endl;
			for (auto a : transportBy)
			{
				cout << a->getModel() << " " << a->getPlates() << ", capacity: " << a->getCapacity() << endl;
			}
			getchar();
			getchar();
		}
		catch (char* ex)
		{
			cout << ex << endl;
		}
	}
	
	if (*choice == 1)
		db->getCliTable()->saveChangesToFile();
	refreshDatabase();
	delete choice;
	
}

void Interface::displayAddNewEmployee()
{
	string newname, newlastname, phone, newlogin, newpass;
	cout << "Create new employee" << endl;
	cout << "Type new employee's name: ";
	cin >> newname;
	cout << "Type new employee's lastname: ";
	cin >> newlastname;
	cout << "Type new employee's phone number: ";
	cin >> phone;
	cout << "Type new employee's login: ";
	cin >> newlogin;
	cout << "Type new employee's password (recommend him to change it later): ";
	cin >> newpass;

	sharedEmpObjPtr empPtr = sharedEmpObjPtr(new Employee(db->getEmpTable()->getIncrementedID(), newname, newlastname, phone, newlogin, newpass));
	db->getEmpTable()->AddToList(empPtr);
	db->getEmpTable()->saveChangesToFile();
	system("cls");
	cout << "Adding the new Employee finished successfully." << endl;
	getchar();
}

void Interface::displayAddNewVehicle()
{
	string newmodel, newplates;
	int eurocap;
	cout << "Add new vehicle" << endl;
	cout << "Type new vehicle's model: ";
	cin >> newmodel;
	cout << "Type new vehicle's plate numbers: ";
	cin >> newplates;
	cout << "Type new vehicle's euro palettes capacity (4, 12 or 24): ";
	do
	{
		cin >> eurocap;
	} while (eurocap != 4 && eurocap != 12 && eurocap != 24);

	sharedVehObjPtr vehPtr = sharedVehObjPtr(new Vehicle(db->getVehTable()->getIncrementedID(), newmodel, newplates, eurocap));
	db->getVehTable()->AddToList(vehPtr);
	db->getVehTable()->saveChangesToFile();
	cout << "Successfully added the new vehicle to the database." << endl;
	getchar();
}

void Interface::displayMainMenu()
{
	system("cls");
	cout << "Welcome to the Database." << endl;
	cout << "Select an option you would like to use." << endl;
	cout << "1. Display all tables." << endl;
	cout << "2. Display single table." << endl;
	cout << "3. Search" << endl;
	cout << "4. Add new record to the base" << endl;
	cout << "5. Modify existing data" << endl;
	cout << "6. Exit" << endl;

	int choice;
	do
	{
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			displayAllTables();
			getchar();
			break;
		case 2:
			system("cls");
			int select;
			cout << "\nSelect table: " << endl;
			cout << "1. Clients table" << endl;
			cout << "2. Parcel Table" << endl;
			cout << "3. Agreement Table" << endl;
			cout << "4. Employee Table" << endl;
			cout << "5. Vehicle Table" << endl;
			do
			{
				cin >> select;
			} while (select<1 || select>5);
			switch(select)
			{
			case 1:
				showTable(db->getCliTable());
				getchar();
				getchar();
				break;
			case 2:
				showTable(db->getParTable());
				getchar();
				getchar();
				break;
			case 3:
				showTable(db->getAgrTable());
				getchar();
				getchar();
				break;
			case 4:
				showTable(db->getEmpTable());
				getchar();
				getchar();
				break;
			case 5:
				showTable(db->getVehTable());
				getchar();
				getchar();
				break;

			}
			break;
		case 3:
			system("cls");
			displaySearchOption();
			getchar();
			break;
		case 4:
			system("cls");
			cout << "Add new record" << endl;
			cout << "1. Vehicle" << endl;
			cout << "2. Employees" << endl;
			cout << "3. Agreement" << endl;
			cout << "0. Back to menu" << endl;
			int add;
			do
			{
				cin >> add;
			} while (add > 3 || add < 0);
			switch (add)
			{
			case 0:
				displayMainMenu();
				break;
			case 1:
				system("cls");
				displayAddNewVehicle();
				break;
			case 2:
				system("cls");
				displayAddNewEmployee();
				break;
			case 3:
				system("cls");
				displayAddNewAgreement();
				break;
			default: 
				break;
			}
			break;
		case 5:
			cout << "\tEdit" << endl;
			cout << "1. Change plate number of a vehicle." << endl;
			cout << "2. Change your password." << endl;
			cout << "0. Back to menu." << endl;
			int edit;
			do
			{
				cin >> edit;
			} while (edit<0 || edit>2);

			switch (edit)
			{
			case 0:
				displayMainMenu();
			case 1:
				system("cls");
				showTable(db->getVehTable());
				displayEditPlateNumber();
				getchar();
				break;
			case 2:
				system("cls");
				displayEditPassword();
				getchar();
				break;
			}
			break;
		case 6: 
			shutDown();
			break;
		default:
			cout << "Choose valid option." << endl;
			getchar();
			break;
		}
	} while (choice < 0 || choice > 6);

}

void Interface::run()
{
	while (!isLogged)
		displayLoginScreen();
	while (isLogged)
		displayMainMenu();
}

void Interface::shutDown()
{
	isLogged = false;
}