/**
* @file ConsoleController.h
* @brief Handles all the console commands.
*
*/

#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>


#include "Typedefs.h"
#include "EmployeeList.h"
#include "MainController.h"
class MainController;
class EmployeeList;

struct Command
{
	std::string commandName;
	std::string commandDesc;
	int argNum;
	int reqPerms;
	callback callbackFnc;
};
//! Handles all commands
//! This is static class! You should never make an object of it!
class ConsoleController
{
	
	static std::vector <Command> CommandList;

public:
	static void PrintWelcomeMessage();
	/**
	  * Main command interface. This is a loop that asks for command input.
	  *
	  *	@param loginsystem Login system to get user permissions.
	  */
	static void CommandHandler(EmployeeList * MainCtrl, MainController * LoginSys);

	/**
	  * Create new command!
	  *
	  *	@param commandName The name of the command that the user has to enter.
	  *	@param nArguments Number of arguments the command needs.
	  *	@param requiredPerms Permissions needed to use this command.
	  * @param callbackFnc The function that will handle the command.
	  * @param description Help text that shows how to use the command.
	  *
	  */
	static void RegisterCommand(std::string commandName, int nArguments, int requiredPerms, callback callbackFnc, std::string description = "");

	/**
	  * Used to get passwords. Hides the input. 
	  *	@returns Inputted string.
	  */
	static std::string hidecin();
};

