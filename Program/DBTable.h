#pragma once
#include "BaseEntity.h"
#include <regex>
#include <memory>
#include <list>

using namespace std;
template<class T = BaseEntity>
class DBTable
{
protected:
	list<shared_ptr<T>> entityList;
public:
	void AddToList(shared_ptr<T> element)
	{
		entityList.push_back(element);
	}

	bool RemoveElementById(int id)
	{
		for (list<shared_ptr<T>>::iterator it = entityList.begin(); it != entityList.end(); ++it)
		{
			if ((*it)->getID() == id)
			{
				entityList.erase(it);
				return true;
			}
		}
		return false;
	}

	shared_ptr<T> getElementById(int id)
	{
		for (list<shared_ptr<T>>::iterator it = entityList.begin(); it != entityList.end(); ++it)
		{
			if ((*it)->getID() == id)
			{
				return (*it);
			}
		}
	}
};