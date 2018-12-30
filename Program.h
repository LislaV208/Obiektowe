#include "Order.h"
#include <vector>

class Program
{
	void showActiveOrders();
	void showArchivalOrders();
	void menuService();
	void productMenuOperations();
	void addProduct();
	void showProductList();
	void findProduct();
	void orderMenuOperations();
	void addOrder();
	void showOrderList();
	void showOrderListMenuOperations();
	void findProductMenuOperations(Product *product);
	void editProduct(Product *product);

public:
	std::vector <Product> _product_list;
	std::vector <Order> _order_list;
	void runProgram();
	class UserInterface
	{
		class Program;
	public:
		void showMenu();
		void showProductMenu();
		void showOrderMenu();
		void showOrderListMenu();
		void findProductMenu();
		static void showProductListHeaders();
		void showPersonHeaders();
	};

private:
	UserInterface userInterface;
};
