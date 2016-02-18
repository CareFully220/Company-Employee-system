#ifndef ECONOMYH
#define ECONOMYH

/*MAJANDUS SÜSTEEM
palk ametitele,
kohamäär (kui suure koormusega 0-1)
tulu sissekanne,
kulude määramine,
kulude/tulude ülevaade(kuu, aasta)

kokkuvõtete genereerimine*/

#include <vector>
#include <string>
#include <fstream>
#include "ConsoleController.h"
#include "Permissions.h"
#include "EmployeeList.h"

struct logEntry {//Struct to store transactions
	int amount;
	std::string type;
	std::string explanation;//DO NOT INCLUDE NEWLINES IN THE EXPLANATION OR THE TYPE.
};

class Economy {
private:
	int money = 0;//In cents
	EmployeeList *EmpList;
	void addMoney(int amount) {
		money += amount;
	};
	std::vector<logEntry*> log;

public:
	Economy(EmployeeList *newEmpList);//The constructor. Loads the save file and registers the ConCmd*s
	int getMoney();//gets the amount of money
	bool ConCmd_add(cmdArgs Args);//Console command for adding money
	bool ConCmd_remove(cmdArgs Args);//Console command for removing money
	bool ConCmd_getMoneyAmount(cmdArgs Args);//Console command for getting the amount of money
	bool ConCmd_getTotalIncome(cmdArgs Args);//Console command for getting the total income
	bool ConCmd_getTotalOutgo(cmdArgs Args);//Console command for getting the total outgo
	bool ConCmd_getVerboseLog(cmdArgs Args);//Print all the transactions in the log
	int add(int amount, std::string explanation);//adds money
	int remove(int amount, std::string type, std::string explanation);//removes money
	const std::vector<logEntry*> getLog();//Gets the log
	int getTotalIncome();//Returns the total income
	int getTotalOutgo();//Returns the total outgo
	void save();//Saves to file
};
#endif