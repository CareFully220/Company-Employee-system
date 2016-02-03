// Company Users.cpp : Defines the entry point for the console application.
// Allahu Akbar

#include "stdafx.h"
#include <iostream>
#include <ctime>
//#include <cstdlib>
#include "InventorySystem.h"


#include "ConsoleController.h"
#include "EmployeeList.h"
#include "MainController.h"

int main()
{
	srand((unsigned int)time(NULL));

	EmployeeList Employees;
	MainController Loginsys;
	Device Inventory;
	// Load employees
	std::cout << "< Loading Employees." << std::endl;
	
	if (Employees.LoadEmployees("EmloyeeData.db")) {
		std::cout << "< Employees loaded successfully!" << std::endl;
	}
	else {
		std::cout << "< No employees found!" << std::endl;
		std::cout << "< Creating Root User..." << std::endl;
		Employees.ConCmd_CreateRoot();

	}
	ConsoleController::PrintWelcomeMessage();
	ConsoleController::CommandHandler(&Employees, &Loginsys);

//	Device go;
//	go.printMenu();

    return 0;
}

