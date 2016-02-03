#pragma once
/**
  * @file EmployeeList.h
  * @brief Includes class that creates a list of employees.
  * You need to include this file if your program uses Employees.
  */

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
	bool ConCmd_Add(cmdArgs Args);
	bool ConCmd_Remove(cmdArgs Args);
	bool ConCmd_List(cmdArgs Args);
	bool ConCmd_Create(cmdArgs Args);
	bool ConCmd_GetInfo(cmdArgs Args);
	bool ConCmd_SetInfo(cmdArgs Args);

	friend MainController;
public:
	//! Constructor. Registers Employee manipulation commands.
	EmployeeList();

	//! Used only once to create root account!
	void ConCmd_CreateRoot();

	/** 
	  * Read employees data from file.
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
	  * Add employee.
	  * @param newEmployee Initialized Employee object.
	  */
	void AddEmployee(Employee newEmployee);

	/**
	* Remove employee.
	* @param id User ID.
	* @returns True if Employee with such id was found and removed. False otherwise.
	*/
	bool RemoveEmployee(int id);

	/**
	* Get info about one Employee.
	* @param id User ID.
	* @param InfoID Information id from the EInfo list.
	* @returns The value of specified Info, if Employee with such id and Information with such id was found.
	*/
	std::string GetEmployeeInfo(int id, EInfo InfoID);

	bool SetEmployeeInfo(int id, EInfo InfoID, std::string newValue);
	
	//! Returns Employee's pointer so it is possible to get it's information.
	//! @returns Pointer to the Employee with the specified ID or nullptr if no Employee with such ID was found.
	Employee* GetEmployeeByID(int id);

	int GetEmployeeCount(); //! Returns the count of the employees on the list.

	
};