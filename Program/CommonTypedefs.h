#pragma once
#include <memory>

class Client;
class Parcel;
class Employee;
class Vehicle;
class Agreement;

typedef std::shared_ptr<Client> sharedCliObjPtr;
typedef std::shared_ptr<Parcel> sharedParObjPtr;
typedef std::shared_ptr<Employee> sharedEmpObjPtr;
typedef std::shared_ptr<Vehicle> sharedVehObjPtr;
typedef std::shared_ptr<Agreement> sharedAgrObjPtr;