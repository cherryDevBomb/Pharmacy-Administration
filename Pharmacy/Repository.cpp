#include "stdafx.h"
#include "Medicine.h"
#include "Repository.h"
#include <string>


//default constructor
Repository::Repository()
{
	list = {};
}


//destructor
Repository::~Repository()
{
}


//getter for list containing all Medicines
std::vector<Medicine> Repository::getList() const
{
	return list;
}


//find a medicine in the list by its name and concentration
Medicine& Repository::findMed(std::string & name, int concentration)
{
	for (size_t i = 0; i < list.size(); i++) {
		if (list[i].getName() == name && list[i].getConcentration() == concentration)
			return list[i];
	}
	Medicine * emptyMed = new Medicine;
	return *emptyMed; //return "empty" medicine if not found
}


//find index of a medicine in the list
int Repository::findMedIndex(std::string & name, int concentration)
{
	for (size_t i = 0; i < list.size(); i++) {
		if (list[i].getName() == name && list[i].getConcentration() == concentration)
			return i; //return index of found medicine
	}
	return -1; //if not found
}


//add medicine object to the list
void Repository::addMed(Medicine& newMed)
{
	list.push_back(newMed);
}


//delete medicine object from the list
void Repository::deleteMed(Medicine & Med)
{
	std::string name = Med.getName();
	int index = findMedIndex(name, Med.getConcentration()); //get index of element to erase
	list.erase(list.begin() + index); //erase element
}


//update price of a medicine
void Repository::updatePrice(Medicine & Med, double newPrice)
{
	Med.setPrice(newPrice);
}


//change medicine quantity
void Repository::addToQuantity(Medicine & Med, int finalQuantity)
{
	Med.setQuantity(finalQuantity);
}


//get a list of medicine with quantity lower than "quantity" function parameter
std::vector<Medicine> Repository::filterByQuantity(std::vector<Medicine> &list, int quantity)
{
	std::vector<Medicine> foundMeds;
	for (Medicine &item : list) {
		if (item.getQuantity() < quantity)
			foundMeds.push_back(item);
	}
	return foundMeds;
}


//extract from the list only medicines conaining given string "pattern"
std::vector<Medicine> Repository::filterByName(std::vector<Medicine> &list, std::string& pattern)
{
	std::vector<Medicine> foundMeds;
	for (Medicine &item : list) {
		if (item.getName().find(pattern) != std::string::npos)
			foundMeds.push_back(item);
	}
	return foundMeds;
}
