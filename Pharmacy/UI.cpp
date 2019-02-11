#include "stdafx.h"
#include "UI.h"
#include <iomanip>
#include "CommandPattern.h"
#include <string>
using namespace std;


//constructor with parameters
UI::UI(const Controller & ctrl, const CommandPattern & cmdPattern)
{
	this->ctrl = ctrl;
	this->cmdPattern = cmdPattern;
}


//destructor
UI::~UI()
{
}


//UI menu
void UI::printMenu()
{
	cout << "    +-------------------------------------+" << endl;
	cout << "    | 1. Add medication                   |" << endl;
	cout << "    | 2. Delete medication                |" << endl;
	cout << "    | 3. Update medication                |" << endl;
	cout << "    | 4. Search by name                   |" << endl;
	cout << "    | 5. See medications in short supply  |" << endl;
	cout << "    | 6. Group by price                   |" << endl;
	cout << "    | 7. UNDO                             |" << endl;
	cout << "    | 8. REDO                             |" << endl;
	cout << "    | 0. Exit                             |" << endl;
	cout << "    +-------------------------------------+" << endl;
}


//add medication
void UI::add()
{
	cout << "Enter name and concentration of medicine to add: ";
	std::string name;
	int concentration;
	cin >> name >> concentration;
	Medicine Med = ctrl.getRepo().findMed(name, concentration);
	if (Med.getName() == "") {	//medicine not yet in list
		cout << "Enter quantity: ";
		int quantity;
		cin >> quantity;
		if (quantity < 0) {
			cout << "Quantity must be greater than 0" << endl << endl;
			return;
		}
		cout << "Enter price: ";
		double price;
		cin >> price;
		if (price <= 0) {
			cout << "Price must be greater than 0" << endl << endl;
			return;
		}
		Medicine tmp(name, concentration, quantity, price);
		Command cmd("addnew", tmp); //create command object
		cmdPattern.pushCommand(cmd, cmdPattern.undoStack); //save command in UNDO stack
		ctrl.addNewMedicine(name, concentration, quantity, price);
		cout << "Medicine successfully added." << endl << endl;
	}
	else {		//medicine already in stock
		cout << "Medicine already in stock. Enter quantity to add: ";
		int quantity;
		cin >> quantity;
		Command cmd("addq", Med); //create command object
		cmdPattern.pushCommand(cmd, cmdPattern.undoStack); //save command in UNDO stack
		ctrl.updateQuantity(name, concentration, quantity);
		cout << "Quantity successfully added." << endl << endl;;
	}
}


//delete medication
void UI::remove()
{
	cout << "Enter name and concentration of medicine to remove: ";
	std::string name;
	int concentration;
	cin >> name >> concentration;
	Medicine Med = ctrl.getRepo().findMed(name, concentration);
	if (Med.getName() == "") {		//medicine not in list
		cout << "This item doesn't exist." << endl << endl;
	}
	else {	//medicine in stock
		Command cmd("delete", Med); //create command object
		cmdPattern.pushCommand(cmd, cmdPattern.undoStack); //save command in UNDO stack
		ctrl.deleteMedicine(name, concentration);
		cout << "Medicine successfully deleted." << endl << endl;
	}
}


//update medication
void UI::update()
{
	cout << "Enter name and concentration of medicine to update: ";
	std::string name;
	int concentration;
	cin >> name >> concentration;
	Medicine Med = ctrl.getRepo().findMed(name, concentration);
	if (Med.getName() == "") {		//medicine not in list
		cout << "This item doesn't exist." << endl << endl;
	}
	else {	//medicine in stock
		cout << "Enter new price: ";
		double newPrice;
		cin >> newPrice;
		if (newPrice < 0) {
			cout << "Price must be greater than 0" << endl << endl;
			return;
		}
		Command cmd("update", Med); //create command object
		cmdPattern.pushCommand(cmd, cmdPattern.undoStack); //save command in UNDO stack
		ctrl.updateMedicine(name, concentration, newPrice);
		cout << "Medicine successfully updated." << endl << endl;
	}
}


//print medicines containing string read from input
void UI::searchByName()
{
	cout << "Enter string contained in the name: ";
	std::string pattern; 
	getline(std::cin, pattern);	   //get pattern to search for
	cout << endl;
	std::vector<Medicine> allMeds = ctrl.getRepo().getList();	//get full list of medicines
	if (pattern != "") {
		allMeds = ctrl.getRepo().filterByName(allMeds, pattern);	//get list of medicines containing pattern
		if (allMeds.size() == 0) {		//if list of found medicines is empty
			cout << "No matches found" << endl << endl;
			return;
		}
	}
	allMeds = ctrl.sortByName(allMeds);	//sort by name
	cout << setw(13) << "NAME" << setw(15) << "CONCENTRATION" << setw(10) << "QUANTITY" << setw(10) << "PRICE" << endl;
	for (Medicine &item : allMeds)
		cout << item;
	cout << endl;
}


//print medications in short suplly
void UI::searchByQuantity()
{
	cout << "Display medicines with quantity less than: ";
	int supply;
	cin >> supply;
	cout << endl;
	if (supply <= 0) {
		cout << "Quantity must be an integer greater than 0" << endl << endl;
		return;
	}
	std::vector<Medicine> allMeds = ctrl.getRepo().getList();	//get full list of medicines
	std::vector<Medicine> found = ctrl.getRepo().filterByQuantity(allMeds, supply);		//get medicines with quantity less than input value
	if (found.size() > 0) {		//at least 1 element found
		found = ctrl.sortByQuantity(found);		//sort medicines by quantity
		cout << setw(13) << "NAME" << setw(15) << "CONCENTRATION" << setw(10) << "QUANTITY" << setw(10) << "PRICE" << endl;
		for (Medicine &item : found)
			cout << item;
	}
	else
		cout << "No medication with quantity less than " << supply << " found" << endl;
	cout << endl;
}


//group all medicines by price
void UI::groupByPrice()
{
	std::vector<Medicine> allMeds = ctrl.getRepo().getList();	//get full list of medicines
	allMeds = ctrl.sortByPrice(allMeds);	//sort medicines by price
	double tmp_price = 0;
	for (Medicine &item : allMeds) {
		if (item.getPrice() > tmp_price) {		//go to next price group
			tmp_price = item.getPrice();		//reset tmp_price
			cout << endl << "  -------------- Price category " << tmp_price << " --------------" << endl;
			cout << setw(13) << "NAME" << setw(15) << "CONCENTRATION" << setw(10) << "QUANTITY" << setw(10) << "PRICE" << endl;
		}
		cout << item; //list all items in the price group
	}
	cout << endl;
}


void UI::run()
{
	char option;
	while (true) {
		system("cls");
		printMenu();
		cout << "Choose option: ";
		cin >> option;
		cin.ignore();

		if (option == '0')
			break;
		else if (option == '1')
			add();
		else if (option == '2')
			remove();
		else if (option == '3')
			update();
		else if (option == '4')
			searchByName();
		else if (option == '5')
			searchByQuantity();
		else if (option == '6')
			groupByPrice();
		else if (option == '7')
			cmdPattern.undo(ctrl);
		else if (option == '8')
			cmdPattern.redo(ctrl);
		else {
			cout << "ERROR. Try again!" << endl;
			system("pause");
			continue;
		}
		system("pause");
	}
}
