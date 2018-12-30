#include "Person.h"

#include <iostream>

using std::cout;
using std::string;

Person::Person()
{
}

Person::Person(string firstName, string lastName, int phoneNumber) :
	_firstName(firstName),
	_lastName(lastName),
	_phoneNumber(phoneNumber) {}

Person::~Person()
{
}

string Person::getFirstName()
{
	return _firstName;
}

string Person::getLastName()
{
	return _lastName;
}

int Person::getPhoneNumber()
{
	return _phoneNumber;
}

void Person::showPerson()
{
	cout.width(20);
	cout << _firstName;
	cout.width(20);
	cout << _lastName;
	cout.width(15);
	cout << _phoneNumber << "\n";
}
