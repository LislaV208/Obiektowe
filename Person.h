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
	string getFirstName() const;
	string getLastName() const;
    int getPhoneNumber() const;
    void showPerson() const;
};
