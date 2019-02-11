#pragma once
#include <string>
#include <iostream>


class Medicine
{
public:
	Medicine();
	Medicine(std::string name, int concentration, int quantity, double price);
	~Medicine();

	std::string getName() const;
	int getConcentration() const;
	int getQuantity() const;
	double getPrice() const;

	void setQuantity(int newQuantity);
	void setPrice(double newPrice);

	friend std::ostream& operator<<(std::ostream& os, const Medicine& med);

private:
	std::string name;
	int concentration;
	int quantity;
	double price;
};

