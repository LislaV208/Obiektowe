#include "Program.h"
#include "Product.h"
#include "Person.h"
#include <conio.h>
#include <iostream>

using std::cout;
using std::string;



void Program::runProgram()
{
	userInterface.showMenu();
	menuService();
}


void Program::menuService()
{
	char c;
	do
	{
		c = _getch();
	} while (c != '1' && c != '2' && c != '3');

	switch (c)
	{
	case '1':
		productMenuOperations();
		break;
	case '2':
		orderMenuOperations();
		break;
	case '3':
		break;
	}
}

void Program::showActiveOrders()
{
	system("cls");
	showOrderList();
}

void Program::showArchivalOrders()
{
	system("cls");
		cout.width(10);
		cout << "Numer";
		cout.width(20);
		cout << "Imie";
		cout.width(20);
		cout << "Nazwisko";
		cout.width(10);
		cout << "Wartosc\n";

		for (int i = 0; i < Order::_amount; i++)
		{
			if (!(_order_list[i].ifActive())) _order_list[i].showOrder();
		}

		showOrderListMenuOperations();

}


void Program::productMenuOperations()
{
	userInterface.showProductMenu();
	char c;
	do
	{
		c = _getch();
	} while (c != '1' && c != '2' && c != '3' && c != '4');

	switch (c)
	{
	case '1':
		showProductList();
		break;
	case '2':
		addProduct();
		break;
	case '3':
		findProduct();
		break;
	case '4':
		runProgram();
		break;
	}
}

void Program::addProduct()
{
	string name;
	float price;
	system("cls");

	cout << "Podaj nazwe produktu: ";
	std::getline(std::cin, name);
	cout << "Podaj cene produktu: ";
	std::cin >> price;
	std::cin.ignore();
	_product_list.push_back(Product(name, price));
	productMenuOperations();
}


void Program::showProductList()
{
	system("cls");
	userInterface.showProductListHeaders();

	for (int i = 0; i < Product::_amount; i++)
	{
		_product_list[i].showProduct();
	}

	cout << "1. POWROT";
	char c;
	do
	{
		c = _getch();
	} while (c != '1');
	productMenuOperations();
}


void Program::findProduct()
{
	system("cls");
	cout << "1. WYSZUKAJ PO NAZWIE PRODUKTU\n";
	cout << "2. WYSZUKAJ PO NUMERZE PRODUKTU\n";

	Product *product = nullptr;
	string name;
	int no;

	char c;
	do
	{
		c = _getch();
	} while (c != '1'&& c != '2');

	system("cls");
	switch (c)
	{
	case '1':
		system("cls");
		cout << "Podaj nazwe produktu: ";
		getline(std::cin, name);
		no = 0;
		break;
	case '2':
		system("cls");
		cout << "Podaj numer produktu: ";
		std::cin >> no;
		name = "";
		break;
	}


	bool ifFind = false;
	for (int i = 0; i < Product::_amount; i++)
	{
		if (_product_list[i].get_name() == name || _product_list[i].get_no() == no)
		{
			product = &_product_list[i];
			ifFind = true;
			break;
		}
	}


	if (ifFind == false)
	{
		system("cls");
		cout << "Nie znaleziono pasujacego produktu\n";
		cout << "1. POWROT";
		char c;
		do
		{
			c = _getch();
		} while (c != '1');
		productMenuOperations();
	}
	else
	{
		system("cls");
		userInterface.showProductListHeaders();
		product->showProduct();
		findProductMenuOperations(product);
	}
}

void Program::orderMenuOperations()
{
	userInterface.showOrderMenu();
	char c;
	do
	{
		c = _getch();
	} while (c != '1' && c != '2' && c != '3' && c != '4');

	switch (c)
	{
	case '1':
		showActiveOrders();
		break;
	case '2':
		showArchivalOrders();
		break;
	case '3':
		Program::addOrder();
		break;
	case '4':
		runProgram();
		break;
	}
}

void Program::addOrder()
{
	system("cls");
	Order *order;
	Person* customer;
	Product product;
	string firstName;
	string lastName;
	int phoneNumber;
	int numberOfProducts;
	int no;
	cout << "Wprowadz dane klienta\n"
		<< "Imie: ";
	std::cin >> firstName;
	cout << "Nazwisko: ";
	std::cin >> lastName;
	cout << "Numer telefonu: ";
	std::cin >> phoneNumber;
	customer = new Person(firstName, lastName, phoneNumber);
	order = new Order(*customer);

	cout << "\nIle produktow chcesz dodac do zamowienia? ";
	std::cin >> numberOfProducts;

	cout << "\nCzy chcesz wyswietlic liste wszystkich produktow?\n"
		<< "1. Tak\n"
		<< "2. Nie\n";
	char c;
	do
	{
		c = _getch();
	} while (c != '1' && c != '2');

	switch (c)
	{
	case '1':
		cout << "\n\n";
		userInterface.showProductListHeaders();
		for (int i = 0; i < Product::_amount; i++)
		{
			_product_list[i].showProduct();
		}
		break;
	case '2':
		break;
	}

	for (int i = 0; i < numberOfProducts; i++)
	{
		cout << "Wprowadz numer " << i + 1 << " produktu: ";
		std::cin >> no;
		product = _product_list[no - 1];
		order->addItem(product);
	}

	_order_list.push_back(*order);
	orderMenuOperations();
}

void Program::showOrderListMenuOperations()
{
	userInterface.showOrderListMenu();
	char c;
	do
	{
		c = _getch();
	} while (c != '1' && c != '2');

	switch (c)
	{
	case '1':
		int no;
		cout << "\nPodaj numer zamowienia ";
		std::cin >> no;
		_order_list[no - 1].showDetails();

		cout << "\n1. PRZENIES DO ARCHIWUM"
			<< "\n2. POWROT";
		char c;
		do
		{
			c = _getch();
		} while (c != '1' && c != '2');
		switch (c)
		{
		case '1':
			_order_list[no - 1].makeArchival();
			break;
		case '2':
			break;
		}
		system("cls");
		showOrderList();
		break;
	case '2':
		orderMenuOperations();
		break;
	}
}

void Program::showOrderList()
{
	cout.width(10);
	cout << "Numer";
	cout.width(20);
	cout << "Imie";
	cout.width(20);
	cout << "Nazwisko";
	cout.width(10);
	cout << "Wartosc\n";

	for (int i = 0; i < Order::_amount; i++)
	{
		if(_order_list[i].ifActive()) _order_list[i].showOrder();
	}

	showOrderListMenuOperations();
}

void Program::findProductMenuOperations(Product*product)
{
	userInterface.findProductMenu();

	char c;
	do
	{
		c = _getch();
	} while (c != '1'&& c != '2' && c != '3');


	switch (c)
	{
	case '1':
		editProduct(product);
		break;
	case '2':
		findProduct();
		break;
	case '3':
		productMenuOperations();
		break;
	}
}

void Program::editProduct(Product *product)
{
	char c;
	string name;
	int price;

	do
	{
		system("cls");
		cout << "1. EDYTUJ NAZWE\n";
		cout << "2. EDYTUJ CENE\n";
		if (product->getAvailability() == true)
		{
			cout << "3. OZNACZ JAKO NIEDOSTEPNY\n";
		}
		else
		{
			cout << "3. OZNACZ JAKO DOSTEPNY\n";
		}
		cout << "4. POWROT";

		do
		{
			c = _getch();
		} while (c != '1' && c != '2' && c != '3' && c != '4');

		switch (c)
		{
		case '1':
			system("cls");
			cout << "Obecna nazwa: " << product->get_name();
			cout << "\nNowa nazwa: ";
			std::getline(std::cin, name);
			product->setName(name);
			break;

		case '2':
			system("cls");
			cout << "Obecna cena: " << product->get_price();
			cout << "\nNowa cena: ";
			std::cin >> price;
			product->setPrice(price);
			break;

		case '3':
			product->changeAvailability();
			break;

		case '4':
			productMenuOperations();
			break;
		}

	} while (c != '4');
}

///INTERFACE
void Program::UserInterface::showMenu()
{
	system("cls");
	cout << "1. PRODUKTY\n"
		<< "2. ZAMOWIENIA\n"
		<< "3. KONIEC\n";
}


void Program::UserInterface::showProductListHeaders()
{
	cout.width(8);
	cout << "Numer";
	cout.width(20);
	cout << "Nazwa produktu";
	cout.width(10);
	cout << "Cena";
	cout.width(15);
	cout << "Dostepnosc\n";
}


void Program::UserInterface::showProductMenu()
{
	system("cls");
	cout << "1. LISTA PRODUKTOW\n"
		<< "2. DODAJ PRODUKT\n"
		<< "3. WYSZUKAJ PRODUKT\n"
		<< "4. POWROT DO MENU\n";
}

void Program::UserInterface::showOrderMenu()
{
	system("cls");
	cout << "1. AKTYWNE ZAMOWIENIA\n"
		<< "2. ARCHIWALNE ZAMOWIENIA\n"
		<< "3. DODAJ ZAMOWIENIE\n"
		<< "4. POWROT DO MENU\n";
}

void Program::UserInterface::showPersonHeaders()
{

	cout.width(20);
	cout << "Imie";
	cout.width(20);
	cout << "Nazwisko";
	cout.width(15);
	cout << "Numer telefonu\n";
}

void Program::UserInterface::showOrderListMenu()
{
	cout << "\n\n1. WYSWIETL SZCZEGOLY WYBRANEGO ZAMOWIENIA"
		<< "\n2. POWROT";
}

void Program::UserInterface::findProductMenu()
{
	cout << "1. EDYTUJ PRODUKT\n";
	cout << "2. WYSZUKAJ KOLEJNY PRODUKT\n";
	cout << "3. POWROT\n";
}
