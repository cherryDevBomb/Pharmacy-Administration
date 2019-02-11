#include "stdafx.h"
#include "Controller.h"
#include <algorithm>


//default constructor
Controller::Controller()
{
}


//constructor with parameters
Controller::Controller(const Repository& repo)
{
	this->repo = repo;
}


//destructor
Controller::~Controller()
{
}


//repository getter
Repository Controller::getRepo() const
{
	return repo;
}


//updates quantity
void Controller::updateQuantity(std::string & name, int concentration, int newQuantity)
{
	Medicine& Med = repo.findMed(name, concentration);
	int finalQuantity = Med.getQuantity() + newQuantity;
	repo.addToQuantity(Med, finalQuantity);
}


//adds a new Medicine with specified attributes to the list
void Controller::addNewMedicine(std::string& name, int concentration, int quantity, double price)
{
	Medicine newMedicine(name, concentration, quantity, price);
	repo.addMed(newMedicine);
}


//deletes a medicine specified by its name and concentration
void Controller::deleteMedicine(std::string& name, int concentration)
{
	repo.deleteMed(repo.findMed(name, concentration));
}


//changes price of a medicine specified by its name and concentration 
void Controller::updateMedicine(std::string& name, int concentration, double newPrice)
{
	repo.updatePrice(repo.findMed(name, concentration), newPrice);
}


//sort Medicines by name alphabetically
std::vector<Medicine>& Controller::sortByName(std::vector<Medicine>& list)
{
	std::sort(list.begin(), list.end(), [](const Medicine & lhs, const Medicine & rhs) {return lhs.getName() < rhs.getName(); });
	return list;
}


//sort Medicines descending by quantity
std::vector<Medicine>& Controller::sortByQuantity(std::vector<Medicine>& list)
{
	std::sort(list.begin(), list.end(), [](const Medicine & lhs, const Medicine & rhs) {return lhs.getQuantity() > rhs.getQuantity(); });
	return list;
}


//sort Medicines ascending by price
std::vector<Medicine>& Controller::sortByPrice(std::vector<Medicine>& list)
{
	std::sort(list.begin(), list.end(), [](const Medicine & lhs, const Medicine & rhs) {return lhs.getPrice() < rhs.getPrice(); });
	return list;
}








