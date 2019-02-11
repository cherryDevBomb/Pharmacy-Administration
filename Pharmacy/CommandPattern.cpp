#include "stdafx.h"
#include "CommandPattern.h"


//command object constructor
Command::Command(std::string operation, Medicine item)
{
	this->operation = operation;
	this->item = item;
}


//getter for operation type
std::string Command::getOp() const
{
	return operation;
}


//getter for previous state item
Medicine Command::getItem() const
{
	return item;
}


//default CommandPattern constructor
CommandPattern::CommandPattern()
{
}


//destructor
CommandPattern::~CommandPattern()
{
}


//save a command in stack specified by function argument
void CommandPattern::pushCommand(Command command, std::vector<Command>& stack)
{
	stack.push_back(command);
}


//get last element from the stack specified by function argument
Command CommandPattern::popCommand(std::vector<Command>& stack)
{
	Command tmp = stack[stack.size() - 1]; //get last element
	stack.erase(stack.begin() + stack.size() - 1); //erase element from the list
	return tmp;
}


//undo option
void CommandPattern::undo(Controller & ctrl)
{
	if (undoStack.size() > 0) {
		Command last = popCommand(undoStack); //pop last executed command
		Medicine previousState = last.getItem(); //get previous state of item
		std::string name = previousState.getName();

		if (last.getOp() == "addq") {				//subtract from quantity
			Medicine currentState = ctrl.getRepo().findMed(name, previousState.getConcentration()); //get current state of element
			int quantity = previousState.getQuantity() - currentState.getQuantity();
			ctrl.updateQuantity(name, previousState.getConcentration(), quantity);
			Command tmp("addq", currentState);
			pushCommand(tmp, redoStack);	//push undone command in redo stack
		}
		else if (last.getOp() == "addnew") {		//delete added item
			ctrl.deleteMedicine(name, previousState.getConcentration());
			pushCommand(last, redoStack); //push undone command in redo stack
		}
		else if (last.getOp() == "delete") {		//add deleted item back
			ctrl.addNewMedicine(name, previousState.getConcentration(), previousState.getQuantity(), previousState.getPrice());
			pushCommand(last, redoStack); //push undone command in redo stack
		}
		else if (last.getOp() == "update") {		//restore previous price
			Medicine currentState = ctrl.getRepo().findMed(name, previousState.getConcentration()); //get current state of element
			ctrl.updateMedicine(name, previousState.getConcentration(), previousState.getPrice());
			Command tmp("update", currentState);
			pushCommand(tmp, redoStack);	//push undone command in redo stack
		}
		std::cout << "Undo successful" << std::endl << std::endl;
	}
	else //no previous operations 
		std::cout << "No undo option available" << std::endl << std::endl;
}


//redo option
void CommandPattern::redo(Controller& ctrl)
{
	if (redoStack.size() > 0) {
		Command last = popCommand(redoStack); //pop last executed command
		Medicine previousState = last.getItem();
		std::string name = previousState.getName();

		if (last.getOp() == "addq") {			//readd quantity
			Medicine currentState = ctrl.getRepo().findMed(name, previousState.getConcentration()); //get current state of element
			int quantity = previousState.getQuantity() - currentState.getQuantity();
			ctrl.updateQuantity(name, previousState.getConcentration(), quantity);
			Command tmp(name, currentState);
			pushCommand(tmp, undoStack);	 //push undone command in undo stack	
		}
		else if (last.getOp() == "addnew") {	//readd element
			ctrl.addNewMedicine(name, previousState.getConcentration(), previousState.getQuantity(), previousState.getPrice());
			pushCommand(last, undoStack); //push undone command in undo stack
		}
		else if (last.getOp() == "delete") {	//redelete element
			ctrl.deleteMedicine(name, previousState.getConcentration());
			pushCommand(last, undoStack); //push undone command in undo stack
		}
		else if (last.getOp() == "update") {	//update price
			Medicine currentState = ctrl.getRepo().findMed(name, previousState.getConcentration()); //get current state of element
			ctrl.updateMedicine(name, previousState.getConcentration(), previousState.getPrice());
			Command tmp("update", currentState);
			pushCommand(tmp, undoStack);	//push undone command in redo stack
		}
		std::cout << "Redo successful" << std::endl << std::endl;
	}
	else	//no previous undo
		std::cout << "No redo option available" << std::endl << std::endl;
}


