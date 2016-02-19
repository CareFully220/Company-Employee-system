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
#include "economy.h"
#include "SalarySystem.h"

#include "ConsoleController.h"
#include "EmployeeList.h"
#include "MainController.h"

int main()
{
	srand((unsigned int)time(NULL));

	// Load employees
	std::cout << "< Loading Employees..." << std::endl;
	EmployeeList Employees;

	if (Employees.LoadEmployees("EmloyeeData.db")) {
		std::cout << "< Employees loaded successfully!" << std::endl;
	}
	else {
		std::cout << "< No employees found!" << std::endl;
		std::cout << "< Creating Root User..." << std::endl;
		Employees.ConCmd_CreateRoot();

	}
	// Inventory System;
	std::cout << "< Loading Devices..." << std::endl;
	Inventory Inv(&Employees);
	cout << "< Devices loaded successfully!" << endl;

	// Economy System;
	Economy economy(&Employees);
	std::cout << "< Loaded Economy System!" << std::endl;

	// Salary System;
	SalarySystem salary(&Employees);
	std::cout << "< Loaded Salary System!" << std::endl;
	
	// CLS;
	ConsoleController::PrintWelcomeMessage();
	ConsoleController::CommandHandler(Employees);

    return 0;
}

