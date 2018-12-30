#pragma once
#include <string>

using std::string;

class Product
{
	string _name;
	float _price;
	int _no;
	bool _availability;

public:
	static int _amount;
	Product();
	Product(string name, float price);
	string get_name();
	float get_price();
	int get_no();
	bool getAvailability();
	void setName(string name);
	void setPrice(int price);
	void changeAvailability();
	void showProduct();
};

