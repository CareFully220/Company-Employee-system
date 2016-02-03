#include "stdafx.h"
#include "MainController.h"



MainController::MainController() 
{
	bLoggedIn = false;
	LoggedUserID = -1;
}
int MainController::LogIn(std::string Username, std::string Password, EmployeeList * EmpList)
{
	if (!bLoggedIn) {
		for (auto &it : EmpList->Employees) {
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