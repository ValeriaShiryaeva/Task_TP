#include "Check.h"

bool intSigned(const string& s);

Check::Check() : Purchase(){}

Check::Check(Product& _product, int _quantity_product, double _purchase_price) :
	Purchase(_product, _quantity_product, _purchase_price) {}

Check::Check(const Check& check) : Purchase(check) {}

void Check::input_purchase(Product& product) {

	Purchase::getProduct().setNameProduct(product.getNameProduct());
	Purchase::getProduct().setCostProduct(product.getCostProduct());
	string _quantity_product;
	cout << "¬веди количество продукта, которое хотите купить: ";
	cin >> _quantity_product;
	if (intSigned(_quantity_product) == true)
		Purchase::setQuantityProduct(stoi(_quantity_product));
	else
		Purchase::setQuantityProduct(0);

	Purchase::setPurchasePrice(product.getCostProduct() * Purchase::getQuantityProduct());
}

void Check::output_product_receipt() {
	cout << Purchase::getProduct().getNameProduct() << "  " << Purchase::getQuantityProduct() 
		<< "  x  " << Purchase::getProduct().getCostProduct() << "  =  " << Purchase::getPurchasePrice() << endl;
}

void Check::output_to_file(ofstream& fout){
	if (!fout.is_open())
		cout << "/t ‘айл Check.txt не открыт" << endl;
	else
		fout << Purchase::getProduct().getNameProduct() << "  " << Purchase::getQuantityProduct()
			<< "  x  " << Purchase::getProduct().getCostProduct() << "  =  " << Purchase::getPurchasePrice() << endl;
}