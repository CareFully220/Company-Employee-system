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

#include "stdafx.h"
#include "MainController.h"



MainController::MainController() 
{
	bLoggedIn = false;
	LoggedUserID = -1;
}
int MainController::LogIn(std::string Username, std::string Password, EmployeeList& EmpList)
{
	if (!bLoggedIn) {
		for (auto &it : EmpList.Employees) {
			if (it.GetUsername().compare(Username) == 0) {  // Check if the username is correct
				if (it.CheckPassword(Password)) { // Check if the password is correct
					if (it.GetPermission(PERM_ALLOWLOGIN) || it.GetPermission(PERM_ROOT)) { // check if user has permission to login
						bLoggedIn = true;
						LoggedUserID = it.GetID();
						return 1;
					}
					else {
						return -1;
					}
				}
				else {
					return -2;
				}
			}
		}
	}
	else {
		return 0;
	}
	return -2;
}
void MainController::LogOut()
{
	 bLoggedIn = false;
	 LoggedUserID = -1;
	 //LoggedEmployee = nullptr;

}
int MainController::GetLoggedInUserID()
{
	return LoggedUserID;
}
bool MainController::IsLoggedIn()
{
	return bLoggedIn;
}