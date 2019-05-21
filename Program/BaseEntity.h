#pragma once
class BaseEntity
{
protected:
	int id;
public:
	BaseEntity();
	BaseEntity(int _id) { id = _id; }
};