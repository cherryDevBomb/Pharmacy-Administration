#pragma once
#include "Controller.h"
#include "CommandPattern.h"

class UI
{
public:
	UI(const Controller & ctrl, const CommandPattern & cmdPattern);
	~UI();

	void printMenu();

	void add();
	void remove();
	void update();
	void searchByName();
	void searchByQuantity();
	void groupByPrice();

	void run();

private:
	Controller ctrl;
	CommandPattern cmdPattern;
};

