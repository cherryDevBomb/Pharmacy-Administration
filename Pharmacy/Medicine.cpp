#include "stdafx.h"
#include "Medicine.h"
#include <iostream>
#include <iomanip>


//default constructor
Medicine::Medicine()
{
	name = "";
	concentration = 0;
	quantity = 0;
	price = 0.0;
}


//constructor wih parameters
Medicine::Medicine(std::string name, int concentration, int quantity, double price)
{
	this->name = name;
	this->concentration = concentration;
	this->quantity = quantity;
	this->price = price;
}


//destructor
Medicine::~Medicine()
{
}


//name getter
std::string Medicine::getName() const
{
	return name;
}


//concentration getter
int Medicine::getConcentration() const
{
	return concentration;
}


//quantity getter
int Medicine::getQuantity() const {
	return quantity;
}


//price getter
double Medicine::getPrice() const
{
	return price;
}


//quantity setter
void Medicine::setQuantity(int newQuantity)
{
	quantity = newQuantity;
}


//price setter
void Medicine::setPrice(double newPrice)
{
	price = newPrice;
}


//output operator overload
std::ostream & operator<<(std::ostream & os, const Medicine & med)
{
	os << std::setw(13) << med.name << std::setw(15) << med.concentration << std::setw(10) << med.quantity << std::setw(10) << med.price << std::endl;
	return os;
}
