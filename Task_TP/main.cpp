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
	cout << "�������� ��������:" << endl;
	cout << "0. ������� ������ ���������" << endl;
	cout << "1. ��������� �������" << endl;
	cout << "2. ���� ��������������" << endl;
	cout << "3. ����� �� ���������" << endl;
}

void selection_products() {
	int key = 27;
	output_products();
	cout << "(����� ��������� ����� ���������, ������� esc)" << endl;
	cout << "(����� ���������� ����� ���������, ������� enter)" << endl;
	while (1) {
		cout << "�������� �������. ";
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
			cout << "� �������� ��� ������ ��������. " << endl;
	}
}

void payment_purchase() {
	output_purchase();
	calculating_total_purchase();
	output_check();
	cout << "�������� �������." << endl;
	cout << "(������� ������ enter)" << endl;
	int key = 13;
	if (key == _getch())
	{
		cout << "������� ��������" << endl << endl;
		purchase.clear();
	}
	else
		cout << "������� �� ��������" << endl << endl;
}

void output_purchase() {
	cout << endl << "������ ��������� � �������" << endl;
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
	cout << "�����: " << total_purchase << endl << endl;
}

void output_check() {
	cout << endl << "���������� ���? 1 - ��������, 2 - �� ��������" << endl;
	double one_purchase, total_purchase = 0;
	int punkt_menu = input_number();
	ofstream fout("Check.txt");
	switch (punkt_menu)
	{
	case 1:
		fout << " �. �����-���������" << endl;
		fout << " ���������� ��-�, 105" << endl;
		fout << "	 �������� ���" << endl << endl;
		for (int i = 0; i < purchase.size(); i++) {
			fout << i + 1 << ". ";
			purchase[i]->output_to_file(fout);
			one_purchase = purchase[i]->getPurchasePrice();
			total_purchase += one_purchase;
		}
		fout << "------------------------------" << endl;
		fout << "�����:   " << total_purchase;
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
	switch (punkt_menu) // �������� switch 
	{
	case 1:
		cout << endl << "������� �� ������ ������� ���������? ";
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
			cout << "������� ��������� �� ������ �������? ";
			quantity_products = input_number();
			if (checking_number_products(quantity_products) == true)
			{
				cout << endl;
				for (int i = 0; i < quantity_products; i++) {
					while (1) {
						cout << "������� ����� ��������, ������ ������ �������: ";
						number_products = input_number();
						if (checking_number_products(number_products) == true)
						{
							products.erase(products.begin() + number_products - 1);
							break;
						}
						else
							cout << "�� ������ �����. " << endl;
					}
				}
				break;
			}
			else
				cout << "�� ������ �����. " << endl;
		}
		cout << endl;
		break;
	case 3:
		output_products();
		break;
	case 4: // ����� �� ���������
		exit(0);
	}
}

void print_menu_administrator() {
	cout << endl << "�������� ��������:" << endl;
	cout << "1. �������� ������� � ������" << endl;
	cout << "2. ������� ������� �� ������" << endl;
	cout << "3. ������� ������ ��������" << endl;
	cout << "4. ����� �� ���������" << endl;
}

void output_products() {
	cout << endl << "������ ��������� � ��������:" << endl;
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
		cout << "������ �����: ";
		cin >> number_s;
		if (intSigned(number_s) == true)
		{
			int number = stoi(number_s);
			return number;
		}
		else
			cout << "������� �� ������ ��������. ��������� ����." << endl;
	}
}

bool intSigned(const string& s) // �������� �� ������ ����� � �����
{
	if (s.find_first_not_of("0123456789", 0) == string::npos)
		return true;
	else
		return false;
}

bool doubleSigned(const string& s) // �������� �� ������ ����� � �����
{
	if (s.find_first_not_of("0123456789.", 0) == string::npos)
		return true;
	else
		return false;
}

bool stringSigned(const string& s) // �������� �� ����� � ������
{
	if (s.find_first_not_of(" qwertyuioplkjhgfdsamnbvcxzPOIUYTREWQLKJHGFDSAMNBVCXZ", 0) == string::npos)
		return true;
	else
		return false;
}