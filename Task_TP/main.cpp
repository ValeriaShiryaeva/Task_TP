#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;

#include "Product.h"
#include "Purchase.h"
#include "Check.h"

vector<Product> products; 
vector<Purchase*> purchase;

bool doubleSigned(const string&);
bool stringSigned(const string&);
bool intSigned(const string&);
bool checking_number_products(int);
int input_number();
void base_products();

void menu();
void print_menu();

void selection_products();
void payment_purchase();
void output_purchase();
void calculating_total_purchase();
void output_check();

void menu_administrator();
void print_menu_administrator();
void output_products();

void main()
{
	setlocale(LC_ALL, "rus");
	base_products();

	while (1)
		menu();
}

void base_products() {

	products.push_back(Product("cucumber", 40));
	products.push_back(Product("tomato", 98));
	products.push_back(Product("cookies", 50));
	products.push_back(Product("cheese", 109));
	products.push_back(Product("bread", 27));
}

void menu() {
	print_menu();
	int punkt_menu = input_number();
	int key;
	switch (punkt_menu)
	{
	case 0:
		output_products();
		break;
	case 1:
		selection_products();
		payment_purchase();
		break;
	case 2:
		menu_administrator();
		break;
	case 3:
		exit(0);
	}
}

void print_menu() {
	cout << "Выберите действие:" << endl;
	cout << "0. Вывести список продуктов" << endl;
	cout << "1. Совершить покупку" << endl;
	cout << "2. Меню администратора" << endl;
	cout << "3. Выйти из программы" << endl;
}

void selection_products() {
	int key = 27;
	output_products();
	cout << "(чтобы закончить выбор продуктов, нажмите esc)" << endl;
	cout << "(чтобы продолжить выбор продуктов, нажмите enter)" << endl;
	while (1) {
		cout << "Выберите продукт. ";
		int number_product = input_number();
		if (checking_number_products(number_product) == true)
		{
			Check* check = new Check;
			check->input_purchase(products.at(number_product - 1));
			purchase.push_back(check);
			if (key == _getch())
				break;
		}
		else
			cout << "В магазине нет такого продукта. " << endl;
	}
}

void payment_purchase() {
	output_purchase();
	calculating_total_purchase();
	output_check();
	cout << "Оплатите покупку." << endl;
	cout << "(нажмите кнопку enter)" << endl;
	int key = 13;
	if (key == _getch())
	{
		cout << "Покупка оплачена" << endl << endl;
		purchase.clear();
	}
	else
		cout << "Покупка не оплачена" << endl << endl;
}

void output_purchase() {
	cout << endl << "Список продуктов в корзине" << endl;
	for (int i = 0; i < purchase.size(); i++) {
		cout << i + 1 << ". ";
		purchase[i]->output_product_receipt();
	}
}

void calculating_total_purchase() {
	double one_purchase, total_purchase = 0;
	for (int i = 0; i < purchase.size(); i++) {
		one_purchase = purchase[i]->getPurchasePrice();
		total_purchase += one_purchase;
	}
	cout << "ИТОГО: " << total_purchase << endl << endl;
}

void output_check() {
	cout << endl << "Напечатать чек? 1 - печатать, 2 - не печатать" << endl;
	double one_purchase, total_purchase = 0;
	int punkt_menu = input_number();
	ofstream fout("Check.txt");
	switch (punkt_menu)
	{
	case 1:
		fout << " г. Санкт-Петербург" << endl;
		fout << " Московский пр-т, 105" << endl;
		fout << "	 КАССОВЫЙ ЧЕК" << endl << endl;
		for (int i = 0; i < purchase.size(); i++) {
			fout << i + 1 << ". ";
			purchase[i]->output_to_file(fout);
			one_purchase = purchase[i]->getPurchasePrice();
			total_purchase += one_purchase;
		}
		fout << "------------------------------" << endl;
		fout << "ИТОГО:   " << total_purchase;
		fout.close();
		break;
	case 2:
		fout.close();
		break;
	case 3:
		exit(0);
	}
}

void menu_administrator() {
	print_menu_administrator();
	int punkt_menu = input_number();
	int quantity_products;
	int number_products;
	switch (punkt_menu) // оператор switch 
	{
	case 1:
		cout << endl << "Сколько вы хотите добавть продуктов? ";
		quantity_products = input_number();
		cout << endl;
		for (int i = 0; i < quantity_products; i++) {
			Product pr1;
			pr1.input_keybord();
			products.push_back(pr1);
		}
		cout << endl;
		break;
	case 2:
		output_products();
		while (1) {
			cout << "Сколько продуктов вы хотите удалить? ";
			quantity_products = input_number();
			if (checking_number_products(quantity_products) == true)
			{
				cout << endl;
				for (int i = 0; i < quantity_products; i++) {
					while (1) {
						cout << "Введите номер продукта, котрый хотите удалить: ";
						number_products = input_number();
						if (checking_number_products(number_products) == true)
						{
							products.erase(products.begin() + number_products - 1);
							break;
						}
						else
							cout << "Не верное число. " << endl;
					}
				}
				break;
			}
			else
				cout << "Не верное число. " << endl;
		}
		cout << endl;
		break;
	case 3:
		output_products();
		break;
	case 4: // выход из программы
		exit(0);
	}
}

void print_menu_administrator() {
	cout << endl << "Выберите действие:" << endl;
	cout << "1. Добавить продукт в список" << endl;
	cout << "2. Удалить продукт из списка" << endl;
	cout << "3. Вывести список продутов" << endl;
	cout << "4. Выйти из программы" << endl;
}

void output_products() {
	cout << endl << "Список продуктов в магазине:" << endl;
	for (int i = 0; i < products.size(); i++) {
		cout << i + 1 << ". ";
		products[i].output_console();
	}
	cout << endl;
}

bool checking_number_products(int number_products) {
	if (number_products <= products.size())
		return true;
	else
		return false;
}

int input_number() {
	string number_s;
	while (1)
	{
		cout << "Ведите номер: ";
		cin >> number_s;
		if (intSigned(number_s) == true)
		{
			int number = stoi(number_s);
			return number;
		}
		else
			cout << "Введено не верное значение. Повторите ввод." << endl;
	}
}

bool intSigned(const string& s) // проверка на только цифры в сроке
{
	if (s.find_first_not_of("0123456789", 0) == string::npos)
		return true;
	else
		return false;
}

bool doubleSigned(const string& s) // проверка на только цифры в сроке
{
	if (s.find_first_not_of("0123456789.", 0) == string::npos)
		return true;
	else
		return false;
}

bool stringSigned(const string& s) // проверка на буквы и пробел
{
	if (s.find_first_not_of(" qwertyuioplkjhgfdsamnbvcxzPOIUYTREWQLKJHGFDSAMNBVCXZ", 0) == string::npos)
		return true;
	else
		return false;
}