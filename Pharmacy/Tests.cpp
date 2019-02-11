#include "stdafx.h"
#include "Tests.h"
#include <cassert>
#include <string>
#include <vector>
#include "Medicine.h"
#include "Repository.h"
#include "Controller.h"



void Tests::testMedicine()
{
	Medicine testMed("Test", 10, 3, 4.88);
	assert(testMed.getName() == "Test");
	assert(testMed.getConcentration() == 10);
	assert(testMed.getQuantity() == 3);
	assert(testMed.getPrice() == 4.88);
}

void Tests::testRepository()
{
	Medicine test1("Paracetamol", 100, 85, 4.55);
	Medicine test2("Nurofen", 400, 55, 15.63);
	Repository testRepo;
	assert(testRepo.getList().size() == 0);
	testRepo.addMed(test1);
	testRepo.addMed(test2);
	assert(testRepo.getList().size() == 2);
	std::string testName = "Paracetamol";
	std::string testName2 = "Another";
	assert(testRepo.findMedIndex(testName, 100) == 0);
	assert(testRepo.findMedIndex(testName2, 100) == -1);
	testRepo.deleteMed(test1);
	assert(testRepo.getList().size() == 1);
	std::vector<Medicine> testList = testRepo.getList();
	std::vector<Medicine> testFound = testRepo.filterByQuantity(testList, 60);
	assert(testFound.size() == 1);
	std::string testPattern = "tamol";
	testFound = testRepo.filterByName(testList, testPattern);

}

void Tests::testController()
{
	std::string testname1 = "Paracetamol";
	std::string testname2 = "Nurofen";
	Repository testRepo;
	Controller testCtrl(testRepo);
	testCtrl.addNewMedicine(testname1, 20, 44, 45.55);
	testCtrl.addNewMedicine(testname2, 20, 44, 43.77);
	assert(testCtrl.getRepo().getList().size() == 2);
	testCtrl.addNewMedicine(testname1, 200, 44, 45.55);
	assert(testCtrl.getRepo().getList().size() == 3);
	testCtrl.deleteMedicine(testname1, 20);
	assert(testCtrl.getRepo().getList().size() == 2);
}

void Tests::testAll()
{
	testMedicine();
	testRepository();
	testController();
}
