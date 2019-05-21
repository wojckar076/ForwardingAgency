#include "Backpack.h"

Backpack::Backpack(){}

Backpack::~Backpack() 
{
	backpackVehicles.clear();
}

bool Backpack::computeBackpack(list<sharedVehObjPtr> vehlist, int parcelsVolume)
{
	if (vehlist.empty())
		return false;
	
	int result = 0;
	bool available24euro = false;
	bool available12euro = false;
	bool available4euro = false;
	bool vehiclesAvailable = true;

	list<sharedVehObjPtr>::iterator it;
	do
	{
		it = vehlist.begin();
		while (it != vehlist.end())
		{
			if ((*it)->getCapacity() == EURO24)
			{
				available24euro = true;
				break;
			}
			++it;
		}
		it = vehlist.begin();
		while (it != vehlist.end())
		{
			if ((*it)->getCapacity() == EURO12)
			{
				available12euro = true;
				break;
			}
			++it;
		}
		it = vehlist.begin();
		while (it != vehlist.end())
		{
			if ((*it)->getCapacity() == EURO4)
			{
				available4euro = true;
				break;
			}
			++it;
		}
		if (available24euro && (abs(parcelsVolume - EURO24) < abs(parcelsVolume - EURO12)) && (abs(parcelsVolume - EURO24) < abs(parcelsVolume - EURO4)))
		{
			result = EURO24;
		}
		else if (available12euro && (abs(parcelsVolume - EURO12) < abs(parcelsVolume - EURO24)) && (abs(parcelsVolume - EURO12) <= abs(parcelsVolume - EURO4)))
		{
			result = EURO12;
		}
		else if (available4euro && (abs(parcelsVolume - EURO4) < abs(parcelsVolume - EURO24)) && (abs(parcelsVolume - EURO4) <= abs(parcelsVolume - EURO12)))
			result = EURO4;
		else result = 0;

		switch (result)
		{
		case EURO24:
			for (it = vehlist.begin(); it != vehlist.end(); ++it)
			{
				if (((*it)->getCapacity() == EURO24) && available24euro)
				{
					parcelsVolume -= (*it)->getCapacity();
					backpackVehicles.push_back(*it);
					vehlist.erase(it);
					available24euro = false;
					break;
				}
				else if (it == vehlist.end())
				{
					result = EURO12;
					break;
				}
			}
			break;
		case EURO12:
			for (it = vehlist.begin(); it != vehlist.end(); ++it)
			{
				if (((*it)->getCapacity() == EURO12) && available12euro)
				{
					parcelsVolume -= (*it)->getCapacity();
					backpackVehicles.push_back(*it);
					vehlist.erase(it);
					available12euro = false;
					break;
				}
				else if (it == vehlist.end())
				{
					result = EURO4;
					break;
				}
			}
			break;
		case EURO4:
			for (it = vehlist.begin(); it != vehlist.end(); ++it)
			{
				if (((*it)->getCapacity() == EURO4) && available4euro)
				{
					parcelsVolume -= (*it)->getCapacity();
					backpackVehicles.push_back(*it);
					vehlist.erase(it);
					available4euro = false;
					break;
				}
				else if (it == vehlist.end())
				{
					cout << "Brakuje pojazdow do przewiezienia wysylki."; //przeniesc do interfejsu gdy computebackpack zwroci false
					vehiclesAvailable = false;
					break;
				}
			}
			break;
		default:
			std::cout << "Something went wrong with the result." << endl; //przeniesc do interfejsu gdy computebackpack zwroci false
			vehiclesAvailable = false;
			break;
		}//switch
	} while (parcelsVolume>0 && vehiclesAvailable);
	
	if (parcelsVolume > 0) return false;
	else
		return true;
}

string Backpack::setStringVehIDs()
{
	stringstream result;
	result << "[";
	for (auto i : backpackVehicles)
	{
		result << i << ",";
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

list<sharedVehObjPtr> Backpack::getBackpackList() { return backpackVehicles; }

list<sharedVehObjPtr> Backpack::getAvailableVehicles(list<sharedVehObjPtr> vehicles)
{
	list<sharedVehObjPtr> result;
	list<sharedVehObjPtr>::iterator it;
	for (it = vehicles.begin(); it != vehicles.end(); ++it)
	{
		if ((*it)->getAvailability() == true)
			result.push_back(*it);
	}
	return result;
}
