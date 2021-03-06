// Pharmacy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Medicine.h"
#include "UI.h"
#include "Tests.h"
#include<iostream>
using namespace std;


int main()
{
	Tests::testAll();

	Repository repo;

	//add some medicine
	Medicine m1("Paracetamol", 100, 85, 4.55);
	Medicine m2("Nurofen", 400, 55, 15.63);
	Medicine m3("Ibuprofen", 400, 104, 15.63);
	Medicine m4("Septolete", 25, 16, 16.75);
	Medicine m5("Strepsils", 100, 111, 15.63);
	Medicine m6("Sinupret", 400, 10, 16.75);
	Medicine m7("Dexametazon", 400, 150, 4.55);
	Medicine m8("Mezim", 25, 16, 12.21);
	repo.addMed(m1);
	repo.addMed(m2);
	repo.addMed(m3);
	repo.addMed(m4);
	repo.addMed(m5);
	repo.addMed(m6);
	repo.addMed(m7);
	repo.addMed(m8);

	Controller ctrl(repo);
	CommandPattern cmdPattern;
	UI ui(ctrl, cmdPattern);
	ui.run();

    return 0;
}

