#pragma once
#include <string>

using std::string;

class Person
{
	string _firstName;
	string _lastName;
	int _phoneNumber;

public:
	Person();
	Person(string firstName, string lastName, int phoneNumber);
	~Person();
	string getFirstName();
	string getLastName();
	int getPhoneNumber();
	void showPerson();
};
