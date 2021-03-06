#include "Program.h"
#include "Product.h"
#include "Person.h"
#include <conio.h>
#include <iostream>

#include <algorithm>
#include <exception>

using std::cout;
using std::string;


void Program::runProgram()
{
	userInterface.showMenu();
	menuService();
}


void Program::menuService()
{
    switch (getUserOptionChoice(3))
	{
    case 1:
		productMenuOperations();
		break;
    case 2:
		orderMenuOperations();
		break;
    case 3:
		break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
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

//		for (int i = 0; i < Order::_amount; i++)
//		{
//			if (!(_order_list[i].isActive())) _order_list[i].showOrder();
//		}

        std::vector<Order> archivalOrders = database.getArchivalOrders();

        std::for_each(archivalOrders.begin(), archivalOrders.end(), [](const Order& order) {
            order.showOrder();
        });

		showOrderListMenuOperations();

}


void Program::productMenuOperations()
{
	userInterface.showProductMenu();

    switch (getUserOptionChoice(4))
	{
    case 1:
		showProductList();
		break;
    case 2:
        addProduct();
		break;
    case 3:
		findProduct();
		break;
    case 4:
		runProgram();
		break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
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

    //zamiast tego niżej
    if (!database.addProduct(new Product(name, price)))
    {
        cout << "Produkt o podanej nazwie znajduje sie juz w bazie\n";
        cout << "Wcisnij dowolny klawisz, aby powrocic";
        getch();
    }
//    _product_list.push_back(Product(name, price));

	productMenuOperations();
}


void Program::showProductList()
{
	system("cls");
	userInterface.showProductListHeaders();

//	for (int i = 0; i < Product::_amount; i++)
//	{
//        _product_list[i].printInfo();
//	}

    std::vector<Product*> products = database.getAllProducts();

    std::for_each(products.begin(), products.end(), [](Product* product){
        product->printInfo();
    });

	cout << "1. POWROT";

    switch (getUserOptionChoice(1))
    {
    case 1:
        productMenuOperations();
        break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
    }
}


void Program::findProduct()
{
	system("cls");
	cout << "1. WYSZUKAJ PO NAZWIE PRODUKTU\n";
	cout << "2. WYSZUKAJ PO NUMERZE PRODUKTU\n";

	Product *product = nullptr;
	string name;
	int no;

    switch (getUserOptionChoice(2))
	{
    case 1:
		system("cls");
		cout << "Podaj nazwe produktu: ";
		getline(std::cin, name);
        product = database.getProduct(name);
		break;
    case 2:
		system("cls");
		cout << "Podaj numer produktu: ";
		std::cin >> no;
        product = database.getProduct(no);
		break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
	}

    if (product == nullptr)
	{
		system("cls");
		cout << "Nie znaleziono pasujacego produktu\n";
		cout << "1. POWROT";

        switch (getUserOptionChoice(1))
        {
        case 1:
            productMenuOperations();
            break;
        default:
            throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
        }

	}
	else
	{
		system("cls");
		userInterface.showProductListHeaders();
        product->printInfo();
		findProductMenuOperations(product);
	}
}

void Program::orderMenuOperations()
{
	userInterface.showOrderMenu();

    switch (getUserOptionChoice(4))
	{
    case 1:
		showActiveOrders();
		break;
    case 2:
		showArchivalOrders();
		break;
    case 3:
        addOrder();
		break;
    case 4:
		runProgram();
		break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
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

    switch (getUserOptionChoice(2))
	{
    case 1:
		cout << "\n\n";
		userInterface.showProductListHeaders();

        // ZADANIE: przerób
		for (int i = 0; i < Product::_amount; i++)
		{
            _product_list[i].printInfo();
		}
		break;
    case 2:
		break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
	}

	for (int i = 0; i < numberOfProducts; i++)
	{
		cout << "Wprowadz numer " << i + 1 << " produktu: ";
		std::cin >> no;
		product = _product_list[no - 1];
		order->addItem(product);
	}

    // ZADANIE: przerób na database
	_order_list.push_back(*order);
	orderMenuOperations();
}

void Program::showOrderListMenuOperations()
{
	userInterface.showOrderListMenu();

    switch (getUserOptionChoice(2))
	{
    case 1:
		int no;
		cout << "\nPodaj numer zamowienia ";
		std::cin >> no;
		_order_list[no - 1].showDetails();

		cout << "\n1. PRZENIES DO ARCHIWUM"
			<< "\n2. POWROT";

        switch (getUserOptionChoice(2))
		{
        case 1:
			_order_list[no - 1].makeArchival();
			break;
        case 2:
			break;
        default:
            throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
		}

		system("cls");
		showOrderList();
		break;
    case 2:
		orderMenuOperations();
		break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
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
        if(_order_list[i].isActive()) _order_list[i].showOrder();
	}

	showOrderListMenuOperations();
}

void Program::findProductMenuOperations(Product*product)
{   
	userInterface.findProductMenu();

    switch (getUserOptionChoice(3))
	{
    case 1:
		editProduct(product);
		break;
    case 2:
		findProduct();
		break;
    case 3:
		productMenuOperations();
		break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
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
            cout << "Obecna nazwa: " << product->getName();
			cout << "\nNowa nazwa: ";
			std::getline(std::cin, name);
			product->setName(name);
			break;

		case '2':
			system("cls");
            cout << "Obecna cena: " << product->getPrice();
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

int Program::getUserOptionChoice(int optionsNumber) const
{
    if (optionsNumber < 1)
        return -1;

    char input;
    const char baseOption = '1';
    bool isInputValid = false;

    while (!isInputValid)
    {
        input = _getch();

        for (int i = 0; i < optionsNumber; ++i)
        {
            if (input == baseOption + i)
            {
                isInputValid = true;
            }
        }
    }

    // lambda, która zamienia char na int
    // moglbym napisac:
    // return input - '0';
    // ale wtedy nie od razu wiadomo o co chodzi. a tak nazwa funkcji mowi co sie dzieje
    // i użylem lambdy, bo nie ma sensu tworzyć zwykłej funkcji, żeby użyć jej tylko w jednym miejscu
    auto charToInt = [](char value) ->int { return (value - '0'); };

    return charToInt(input);
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
