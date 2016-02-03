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
* @file ConsoleController.h
* @brief Everything related to Commands.
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

//! Single command.
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
	  *	@param MainCtrl Pointer to the EmployeeList used by Login system.
	  *	@param LoginSys Pointer to Login system to get user permissions.
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

