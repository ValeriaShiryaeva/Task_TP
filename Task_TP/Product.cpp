#include "Product.h"

bool doubleSigned(const string& s);
bool stringSigned(const string& s);

Product::Product() : name_product("uncounted"), cost_product(0) {}

Product::Product(string _name_producuct, double _cost) : name_product(_name_producuct), cost_product(_cost) {}

Product::Product(const Product& product) : name_product(product.name_product), cost_product(product.cost_product) {}

void Product::input_keybord() {
	string name_product_s, cost_s;
	cout << "¬ведите название продукта: ";
	cin >> name_product_s;
	if (stringSigned(name_product_s) == true)
		setNameProduct(name_product_s);
	else
		setNameProduct("uncounted");

	cout << "¬ведите стоимость продукта: ";
	cin >> cost_s;
	if (doubleSigned(cost_s) == true)
		setCostProduct(stod(cost_s));
	else
		setCostProduct(0);
}

void Product::output_console() {
	cout << getNameProduct() << "    " << getCostProduct() << endl;
}

bool Product::operator==(Product& product) {
	return name_product == product.getNameProduct() && cost_product == product.getCostProduct();
}
