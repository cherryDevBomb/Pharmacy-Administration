#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "Medicine.h"
#include "Controller.h"


//saves operation performed by a command
class Command
{
public:
	Command(std::string operation, Medicine item);
	std::string getOp() const;
	Medicine getItem() const;
private:
	std::string operation; //operation performed by a command
	Medicine item; //previous state of item on which the operation was performed
};



class CommandPattern
{
public:
	CommandPattern();
	~CommandPattern();

	void pushCommand(Command command, std::vector<Command>& stack);
	Command popCommand(std::vector<Command>& stack);

	void undo(Controller& ctrl);
	void redo(Controller& ctrl);

private:
	std::vector<Command> undoStack;
	std::vector<Command> redoStack;
	friend class UI;
};

