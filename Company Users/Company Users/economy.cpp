#include "stdafx.h"
#include "economy.h"

Economy::Economy(EmployeeList *newEmpList) {
	EmpList = newEmpList;
	using namespace std::placeholders;
	//register the commands
	ConsoleController::RegisterCommand("addmoney",
		2,
		PERM_USER,
		std::bind(&Economy::ConCmd_add, this, _1),
		"Params: <amount> <description> | Adds money.");
	ConsoleController::RegisterCommand("removemoney",
		3,
		PERM_MODIFYSALARY,
		std::bind(&Economy::ConCmd_remove, this, _1),
		"Params: <amount> <type> <description> | Removes money.");
	ConsoleController::RegisterCommand("gettotalincome",
		0,
		PERM_VIEWSALARY,
		std::bind(&Economy::ConCmd_getTotalIncome, this, _1),
		"Get the total income");
	ConsoleController::RegisterCommand("gettotaloutgo",
		0,
		PERM_VIEWSALARY,
		std::bind(&Economy::ConCmd_getTotalOutgo, this, _1),
		"Get the total outgo");
	ConsoleController::RegisterCommand("getvtransactlog",
		0,
		PERM_VIEWSALARY,
		std::bind(&Economy::ConCmd_getVerboseLog, this, _1),
		"Get verbose logs of transactions");
	ConsoleController::RegisterCommand("countmoney",
		0,
		PERM_VIEWSALARY,
		std::bind(&Economy::ConCmd_getMoneyAmount, this, _1),
		"Print the amount of money we have");
	//Read the save
	std::ifstream iFile("economy");
	std::string buf;
	logEntry *nLogEntry;
	std::getline(iFile, buf);
	money = atoi(buf.c_str());
	while (iFile.good()) {
		nLogEntry = new logEntry();
		std::getline(iFile, buf);
		if (buf[0] == '\0')//If the line was empty
			break;
		nLogEntry->amount = atoi(buf.c_str());
		std::getline(iFile, nLogEntry->explanation);
		std::getline(iFile, nLogEntry->type);
		log.push_back(nLogEntry);
	}
	iFile.close();
};

bool Economy::ConCmd_add(cmdArgs Args) {//Console command for adding money
	int amount = atoi(Args[0].c_str());
	//The explanation will be "username: Rest of the arguments" 
	std::string explanation = " " + EmpList->GetEmployeeInfo(MainController::GetLoggedInUserID(), EINF_FIRSTNAME) + ":";
	for (int i = 1; i < (int)Args.size(); i++) {
		explanation += " " + Args[i];
	}
	//Don't remove money with the addmoney command
	if (amount <= 0) {
		return 0;
	}
	add(amount, explanation);
	save();//Save to the file
	return 1;
};

bool Economy::ConCmd_remove(cmdArgs Args) {
	int amount = atoi(Args[0].c_str());
	std::string type = Args[1];
	//The explanation will be "username: Rest of the arguments"
	std::string explanation = " " + EmpList->GetEmployeeInfo(MainController::GetLoggedInUserID(), EINF_FIRSTNAME) + ":";
	for (int i = 2; i < (int)Args.size(); i++) {
		explanation += " " + Args[i];
	}
	//Don't add money with the removemoney command
	if (amount <= 0) {
		return 0;
	}
	if ((money - amount) < 0) {
		std::cout << "Not enough money\n";
		return 1;
	}
	remove(amount, type, explanation);
	save();//Save to the file
	return 1;
};

bool Economy::ConCmd_getMoneyAmount(cmdArgs Args) {//Console command for getting the amount of money
	std::cout << getMoney() << "\n";
	return 1;
};

bool Economy::ConCmd_getTotalIncome(cmdArgs Args) {//Console command for getting the total income
	std::cout << getTotalIncome() << "\n";
	return 1;
};

bool Economy::ConCmd_getTotalOutgo(cmdArgs Args) {//Console command for getting the total outgo
	std::cout << getTotalOutgo() << "\n";
	return 1;
};

bool Economy::ConCmd_getVerboseLog(cmdArgs Args) {//Print all the transactions in the log
	for (int i = 0; i < (int)log.size(); i++) {
		std::cout << log[i]->amount << " type: " << log[i]->type << log[i]->explanation << "\n";
	}
	return 1;
};

int Economy::getMoney() {//gets the amount of money
	return money;
};

int Economy::add(int amount, std::string explanation) {//adds money
											  //DO NOT INCLUDE NEWLINES IN THE EXPLANATION(TODO: check for newlines and remove em)
	logEntry *nLogEntry = new logEntry();
	addMoney(amount);
	nLogEntry->amount = amount;
	nLogEntry->explanation = explanation;
	nLogEntry->type = "PROFIT";
	log.push_back(nLogEntry);
	return 1;
};

int Economy::remove(int amount, std::string type, std::string explanation) {//removes money
																   //DO NOT INCLUDE NEWLINES IN THE EXPLANATION
	if (amount + money < 0) {
		std::cout << "Total money <0";
		return 0;
	}
	logEntry *nLogEntry = new logEntry();
	addMoney(0 - amount);
	nLogEntry->amount = 0 - amount;
	nLogEntry->explanation = explanation;
	nLogEntry->type = type;
	log.push_back(nLogEntry);
	return 1;
};

const std::vector<logEntry*> Economy::getLog() {
	return log;
};

int Economy::getTotalIncome() {//income
	int income = 0;
	for (int i = 0; i < (int)log.size(); i++) {
		if (log[i]->type == "PROFIT") {
			income += log[i]->amount;
		}
	}
	return income;
};

int Economy::getTotalOutgo() {//Returns the total outgo
	int outgo = 0;//Seems like some legit english
	for (int i = 0; i < (int)log.size(); i++) {
		if (log[i]->type != "PROFIT") {
			outgo += log[i]->amount;
		}
	}
	return outgo;
};

void Economy::save() {//Saves to file
	std::ofstream oFile("economy");
	oFile << money << "\n";
	for (int i = 0; i < (int)log.size(); i++) {
		oFile << log[i]->amount << "\n";
		for (int ii = 0; ii < (int)log[i]->explanation.size(); ii++)
			oFile.put(log[i]->explanation[ii]);
		oFile.put('\n');
		for (int ii = 0; ii < (int)log[i]->type.size(); ii++)
			oFile.put(log[i]->type[ii]);
		oFile.put('\n');
	}
	oFile.close();
};