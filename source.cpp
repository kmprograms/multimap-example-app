#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

struct Product
{
	std::string name;
	double price;

	bool operator<(const Product& product) const
	{
		if (this->name == product.name)
		{
			return this->price < product.price;
		}
		return this->name < product.name;
	}

	friend std::ostream& operator<<(std::ostream& out, const Product& product)
	{
		return out << "[ " << product.name << ", " << product.price << " ]";
	}
};

int main()
{
	auto product_a = Product{ "PROD A", 21.1 };
	auto product_b = Product{ "PROD B", 32.4 };
	auto product_c = Product{ "PROD C", 47.2 };

	std::multimap<Product, int> products_with_quantity;
	products_with_quantity.emplace(product_a, 11);
	products_with_quantity.emplace(product_a, 15);
	products_with_quantity.emplace(product_a, 12);
	products_with_quantity.emplace(product_b, 19);
	products_with_quantity.emplace(product_b, 21);
	products_with_quantity.emplace(product_b, 4);
	products_with_quantity.emplace(product_c, 35);
	products_with_quantity.emplace(product_c, 41);
	products_with_quantity.emplace(product_c, 23);

	std::cout << "SORTED PRODUCTS WITH QUANTITIES" << std::endl;
	for (const auto& [key, value] : products_with_quantity)
	{
		std::cout << key << " QUANTITY: " << value << std::endl;
	}

	std::cout << "\nNUMBER OF PRODUCTS WITH NAME " << product_a.name << std::endl;
	int number_of_products = products_with_quantity.count(product_a);
	std::cout << number_of_products << std::endl;

	auto products_range = products_with_quantity.equal_range(product_a);

	std::vector<int> product_quantities(std::distance(products_range.first, products_range.second));
	std::transform( products_range.first, products_range.second, product_quantities.begin(), 
		[](const std::pair<Product, int>& p) {return p.second; });
	
	double sum = std::accumulate(product_quantities.begin(), product_quantities.end(), 0.0);
	double average_quantity = number_of_products == 0 ? 0 : sum / number_of_products;
	std::cout << "\nAVERAGE QUANTITY = " << average_quantity << std::endl;

	auto max_quantity_iterator = std::max_element(product_quantities.begin(), product_quantities.end());
	std::cout << "\nMAX QUANTITY = " << *max_quantity_iterator << std::endl;
	
	return 0;
}