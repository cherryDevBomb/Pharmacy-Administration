#pragma once
#include "Repository.h"

class Controller
{
public:
	Controller();
	Controller(const Repository& repo);
	~Controller();

	Repository getRepo() const;

	void updateQuantity(std::string& name, int concentration, int newQuantity);
	void addNewMedicine(std::string& name, int concentration, int quantity, double price);
	void deleteMedicine(std::string& name, int concentration);
	void updateMedicine(std::string& name, int concentration, double newPrice);

	std::vector<Medicine>& sortByName(std::vector<Medicine>& list);
	std::vector<Medicine>& sortByQuantity(std::vector<Medicine>& list);
	std::vector<Medicine>& sortByPrice(std::vector<Medicine>& list);

private:
	Repository repo;
};

