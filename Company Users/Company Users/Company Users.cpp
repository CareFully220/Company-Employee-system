/* *********************************************************************
* Employee User System
* Copyright 2016 Marvin Hestein & Lauri Mäe
*
* This file is part of Employee User System and is it's entry point.
*
* Employee User System is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Employee User System 2k16 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Employee User System. If not, see <http://www.gnu.org/licenses/>.
*
* ********************************************************************/

/** @file "Company Users.cpp"
  * @brief Defines the entry point for the application.
  */

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
	//MainController Loginsys;
	Inventory Inv;
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
	ConsoleController::CommandHandler(Employees);

//	Device go;
//	go.printMenu();

    return 0;
}

