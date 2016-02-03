#pragma once
/**
* @file MainController.h
* @brief Controls the user login action. 
* 
*
*/
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