/* *********************************************************************
* Employee User System
* Copyright 2016 Marvin Hestein, Lauri Mäe
*
* This file is part of Employee User System.
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

/**
  * @file EmployeeList.h
  * @brief Creates a list of employees.
  */
#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Typedefs.h"
#include "Employee.h"
#include "ConsoleController.h"


class ConsoleController;
class MainController;
/**
  * Creates a list of employees and everything required to modify the list.
  */
class EmployeeList
{
protected:
	std::vector <Employee> Employees;

	// Command Callbacks
	bool ConCmd_Load(cmdArgs Args);
	bool ConCmd_Save(cmdArgs Args);
	bool ConCmd_Remove(cmdArgs Args);
	bool ConCmd_List(cmdArgs Args);
	bool ConCmd_ListSort(cmdArgs Args);
	bool ConCmd_Create(cmdArgs Args);
	bool ConCmd_CreateUser(cmdArgs Args);
	bool ConCmd_GetInfo(cmdArgs Args);
	bool ConCmd_SetInfo(cmdArgs Args);
	bool ConCmd_ListPerms(cmdArgs Args);
	bool ConCmd_ModifyPerms(cmdArgs Args);

	friend MainController;
public:
	//! Constructor. Registers Employee manipulation commands.
	EmployeeList();

	//! Used only once to create root account!
	void ConCmd_CreateRoot();

	/**
	  * Read employees data from file. Only called once at the beginning.
	  *
	  * @param FileName The name of the file that includes all the data of the Employees.
	  * @returns True if any Employee was found, false if no employee was found or there was no file.
	  */
	bool LoadEmployees(std::string FileName );

	/**
	  * Save employees data to file.
	  * @param FileName The name of the file that includes all the data of the Employees.
	  */
	void SaveEmployees(std::string FileName );

	/**
	  * Add employee to the list.
	  * @param newEmployee Initialized Employee object.
	  */
	void AddEmployee(Employee newEmployee);

	/**
	* Remove employee.
	* @param id User ID.
	* @returns 1 if Employee with such id was found and removed.
	* @returns 0 if Employee with such id was found but already removed.
	* @returns -1 if Employee with such id was not found.
	*/
	int RemoveEmployee(int id);

	/**
	* Get info about one Employee.
	* @param id User ID.
	* @param InfoID Information id from the EInfo list.
	* @returns The value of specified Info, if Employee with such id and Information with such id was found.
	*/
	std::string GetEmployeeInfo(int id, EInfo InfoID);

	/**
	* Set Employee's information.
	* @param id User ID.
	* @param InfoID Information id from the EInfo list.
	* @param newValue New value.
	* @returns True if successful. False Employee with such id and/or Information with such id was not found.
	*/
	bool SetEmployeeInfo(int id, EInfo InfoID, std::string newValue);
	
	//! Returns true if Employee with given id exists.
	bool IsValidID(int id);
	


	int GetEmployeeCount(); //!< Returns the count of the employees on the list.

	//! Returns Employee's pointer so it is possible to get it's information.
	//! If possible, do not use this, use GetEmployeeInfo() instead.
	//! @returns Pointer to the Employee with the specified ID or nullptr if no Employee with such ID was found.
	Employee* GetEmployeeByID(int id);
	
};