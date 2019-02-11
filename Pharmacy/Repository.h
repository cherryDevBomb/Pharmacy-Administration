#pragma once
#include "stdafx.h"
#include "Medicine.h"
#include <iostream>
#include <vector>

class Repository
{
public:
	Repository();
	~Repository();

	std::vector<Medicine> getList() const;

	Medicine& findMed(std::string& name, int concentration);
	int findMedIndex(std::string& name, int concentration);

	void addMed(Medicine& Med);
	void deleteMed(Medicine& Med);
	void updatePrice(Medicine& Med, double newPrice);
	void addToQuantity(Medicine& Med, int finalQuantity);

	std::vector<Medicine> filterByName(std::vector<Medicine> & list, std::string& pattern);
	std::vector<Medicine> filterByQuantity(std::vector<Medicine> & list, int quantity);

private:
	std::vector<Medicine> list;
};

