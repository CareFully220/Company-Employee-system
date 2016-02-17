#pragma once
#ifndef SALARYSYSTEM_H
#define SALARYSYSTEM_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "ConsoleController.h"
#include "Permissions.h"


class SalarySystem {
private:
	//'s' means string
	std::string sID;
	std::string sWorkHours;
	std::string sJobPayRate;
	std::string sSalary;
	std::string sFica;
	std::string sUip;
	std::string sSalaryExpense;
	std::string sBonus;
	std::string sBonusFica;
	std::string sBonusUip;
	std::string sBonusExpense;
	std::string sTotalExpense;

	//vector to store data
	std::vector<SalarySystem> salaryList;

	//employee list pointer
	EmployeeList *EmpList;

	//Federal Insurance Contributions Act rate (sotsiaalmaksu määr) 
	const float ficaRate = 0.33f;

	//Unemployment insurance rate (töötuskindlustusmaksu määr) 
	const float uipRate = 0.008f;

	SalarySystem();

protected:
	//gets employee worked hours from employee list
	bool ConCmd_GetWorkHours(cmdArgs Args);

	//changes employee salary
	//bool ConCmd_ModifySalary(cmdArgs Args);


	//test command
	bool ConCmd_Test1(cmdArgs Args);

	
public:
	//default constructor
	SalarySystem(EmployeeList *EmpList);

	//constructor for adding employee expense info
	SalarySystem(int ID, int workHours, float jobPayRate, float salary,
		float fica, float uip, float salaryExpense, float bonus,
		float bonusFica, float bonusUip, float bonusExpense, float totalExpense)
	{
		sID = std::to_string(ID);
		sWorkHours = std::to_string(workHours);
		sJobPayRate = std::to_string(jobPayRate);
		sSalary = std::to_string(salary);
		sFica = std::to_string(fica);
		sUip = std::to_string(uip);
		sSalaryExpense = std::to_string(salaryExpense);
		sBonus = std::to_string(bonus);
		sBonusFica = std::to_string(bonusFica);
		sBonusUip = std::to_string(bonusUip);
		sBonusExpense = std::to_string(bonusExpense);
		sTotalExpense = std::to_string(totalExpense);
	}

	//calculates employee salary
	float calSalary(float workHours, float jobPayRate);

	//calculates fica tax
	float calFica(float salary);

	//calculates uip tax
	float calUip(float salary);

	//calculates uip tax
	float calSalaryExpense(float salary, float fica, float uip);

	//calculates bonus fica tax
	float calBonusFica(float bonus);

	//calculates uip tax
	float calBonusUip(float bonus);

	//calculates total expense per employee
	float calExpense(float salary, float fica, float uip);

	//calculates total bonus expense per employee
	float calBonusExpense(float bonus, float bonusFica, float bonusUip);

	//calculates total bonus expense per employee
	float calTotalExpense(float salaryExpense, float bonusExpense);

	//loads employee total expense database
	void loadFile();

	//saves changes
	void saveFile();

	//adds new employee expense
	void addExpense();


	//get functions
	std::string getID();
	std::string getWorkHours();
	std::string getJobPayRate();
	std::string getSalary();
	std::string getFica();
	std::string getUip();
	std::string getSalaryExpense();
	std::string getBonus();
	std::string getBonusFica();
	std::string getBonusUip();
	std::string getBonusExpense();
	std::string getTotalExpense();
};

#endif