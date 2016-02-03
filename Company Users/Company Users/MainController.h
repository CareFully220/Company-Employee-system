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
* @file MainController.h
* @brief Controls the user login action. 
* 
*
*/
#pragma once

#include <string>
#include "EmployeeList.h"


class EmployeeList;

class MainController
{
	bool bLoggedIn;
	int LoggedUserID;
public:
	MainController();

	int GetLoggedInUserID();

	/** Tries to login with the username and password given.
	  *
	  * @returns  1 if login was successful. 
	  * @returns  0 if there is someone logged in already.
	  * @returns -1 if user has no permissions to login.
	  * @returns -2 if login failed because the username or password was wrong.
	  */
	int LogIn(std::string Username, std::string Password, EmployeeList * EmpList);
	
	//! Logs out the user.
	void LogOut();

	bool IsLoggedIn();
};