/* *********************************************************************
* Employee User System
* Copyright 2016 Marvin Hestein, Lauri M�e
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
#include "EmployeeList.h"

bool EmployeeList::LoadEmployees(std::string FileName )
{
	std::ifstream file(FileName); // Open the file for writing

	if (!file.is_open()) return false; // If there is no file open

	std::string szBuffer; // Buffer to store selected line

	
	while (std::getline(file, szBuffer)) {
		std::string UserData[13];
		int iUserData[2];
		// Check if the line is empty
		if (szBuffer[0] != '\0') {
			std::string szField;
			std::stringstream ss(szBuffer);
			std::string vName;
			for (int i = 0; i < 13; i++) {
				getline(ss, szField, '"');
				// Get the variable name
				getline(ss, szField, '"');
				if (szField[0] == '\0') continue;
				UserData[i] = szField;
			}
			iUserData[0] = atoi(UserData[0].c_str());
			iUserData[1] = atoi(UserData[12].c_str());
			AddEmployee(Employee( iUserData[0], UserData[1], UserData[2], UserData[3], UserData[4], UserData[5], UserData[6], UserData[7], UserData[8], UserData[9], UserData[10], UserData[11], iUserData[1]));
		}
	}
	if (GetEmployeeCount()) 
		return true;
	else 
		return false;
	
}


void EmployeeList::SaveEmployees(std::string FileName )
{
	std::ofstream file(FileName); // Open the file for writing

	for (auto &it : Employees) {
		/*Employee(
		std::string firstname, std::string lastname,
		std::string SSID, std::string address, 
		std::string gender, std::string position, 
		std::string education, std::string nationality,
		std::string username, std::string password, std::string salt, int permissions);*/
		file << "\"" << it.GetID() << "\" \""
			<< it.GetInfo(EINF_FIRSTNAME) << "\" \""
			<< it.GetInfo(EINF_LASTNAME) << "\" \""
			<< it.GetInfo(EINF_SSID) << "\" \""
			<< it.GetInfo(EINF_ADDRESS) << "\" \""
			<< it.GetInfo(EINF_GENDER) << "\" \""
			<< it.GetInfo(EINF_POSITION) << "\" \""
			<< it.GetInfo(EINF_EDUCATION) << "\" \""
			<< it.GetInfo(EINF_NATIONALITY) << "\" \""
			<< it.GetUsername() << "\" \""
			<< it.GetPassword() << "\" \""
			<< it.GetSalt() << "\" \""
			<< it.GetPermissions() << "\"" << std::endl;
	}
	file.close();
}

// Adds employee
void EmployeeList::AddEmployee(Employee newEmployee)
{
	Employees.push_back(newEmployee);
}

// Remove employee
int EmployeeList::RemoveEmployee(int id)
{
	for (auto it = Employees.begin(); it != Employees.end(); it++) {
		if (it->GetID() == id) {
			if (!it->IsRemoved()) {
				it->AddPermission(PERM_DELETED);
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return -1;
}
int EmployeeList::GetEmployeeCount() //Returns value of how many employees are there
{
	return (int)Employees.size();
}
/*Employee* EmployeeList::GetEmployee(int index) {
	if (index >= 0 && index < GetEmployeeCount())
		return &Employees[index];
	else
		return nullptr;
}*/
bool EmployeeList::IsValidID(int id) {
	for (int i = 0; i < GetEmployeeCount(); i++) {
		if (Employees[i].GetID() == id && !Employees[i].IsRemoved()) {
			return true;
		}
	}
	return false;
}
Employee* EmployeeList::GetEmployeeByID(int id) {
	for (int i = 0; i < GetEmployeeCount(); i++) {
		if (Employees[i].GetID() == id && !Employees[i].IsRemoved()) {
			return &Employees[i];
		}
	}
	return nullptr;
}
std::string EmployeeList::GetEmployeeInfo(int id, EInfo InfoID)
{
	Employee * tempEmp = GetEmployeeByID(id);
	if (tempEmp != nullptr && !tempEmp->IsRemoved())
		return tempEmp->GetInfo(InfoID);

	return "";
}
bool EmployeeList::SetEmployeeInfo(int id, EInfo InfoID, std::string newValue)
{
	Employee * tempEmp = nullptr;
	tempEmp = GetEmployeeByID(id);
	if (tempEmp != nullptr) {
		ConsoleController::replaceAll(newValue, "\"", "");
		tempEmp->SetInfo(InfoID, newValue);
		return true;
	}
	else {
		return false;
	}
}

// Command Callbacks
bool EmployeeList::ConCmd_Load(cmdArgs Args)
{
	return true;
}
bool EmployeeList::ConCmd_Save(cmdArgs Args)
{
	SaveEmployees("EmloyeeData.db");
	std::cout << "Employees saved successfully!" << std::endl;
	return true;
}
bool EmployeeList::ConCmd_Remove(cmdArgs Args)
{
	// Get arguments
	int id = atoi(Args[0].c_str());

	// Logged in user id
	int luserid = MainController::GetLoggedInUserID();
	// Check if Employee that the user is trying to remove is currently logged in.
	if (luserid == id) {
		std::cout << "You are currently logged in with this user. You can't remove it!" << std::endl;
		return true;
	}
	// Get employee pointer so we can work on it more easily
	Employee * TempEmp = GetEmployeeByID(id);
	
	if (TempEmp != nullptr) {
		// Check if the Employee that the user is trying to remove is an admin,
		// and if the user who is deleting is not an admin.
		if (TempEmp->GetPermission(PERM_ADMIN) && !(GetEmployeeByID(luserid)->GetPermission(PERM_ADMIN))) { // Pretty badly optimized. sorry.
				std::cout << "The employee you are trying to remove is an admin!" << std::endl;
				std::cout << "Only admins can remove admin accounts!" << std::endl;
				return true;
		}
	}
	else {
		std::cout << "Didn't find Employee with ID: " << id << std::endl;
		return true;
	}

	// Remove Employee
	int retval = RemoveEmployee(id); 
	// Check if it failed
	if (retval == 1) {
		std::cout << "Successfully removed Employee ID: " << id << std::endl;
		return true;
	}
	else {
		std::cout << "Employee with ID " << id << " is already removed!" << std::endl;
		return true;
	}
}
bool EmployeeList::ConCmd_List(cmdArgs Args)
{
	std::cout << " ID    | Name                    | Username" << std::endl;
	std::cout << "=======================================================" << std::endl;
	for (auto &it : Employees) {
		if (!it.IsRemoved()){
			std::string temp;
			std::stringstream spaces;

			temp = " [" + std::to_string(it.GetID()) + "] "; // Format id column.
			for (int i = 9 - temp.length(); i > 0; i--) spaces << " "; // Calculate the number of spaces we need to add.
			std::cout << temp << spaces.str(); // Print the ID with the spaces
			// Reset and clear space string
			spaces.str(std::string());
			spaces.clear();

			temp = it.GetInfo(EINF_FIRSTNAME) + " " + it.GetInfo(EINF_LASTNAME);  // Format name column.
			for (int i = 26 - temp.length(); i > 0; i--) spaces << " "; // Calculate the number of spaces we need to add.
			std::cout << temp << spaces.str(); // Print the name with the spaces
			std::cout << it.GetUsername() << std::endl; // Print the Username. Since nothing will come after this, we don't need to calculate the spaces.
		}
	}
	return true;
}
bool EmployeeList::ConCmd_ListSort(cmdArgs Args)
{
	std::string infoName = Args[0];
	// Change entered info name to lowercase.
	std::transform(infoName.begin(), infoName.end(), infoName.begin(), tolower);

	EInfo infoID = EINF_INVALID;
	for (int i = 0; i < EINFOS; i++) {
		if (EmployeeInfoNames[i].compare(infoName) == 0) {
			infoID = (EInfo)i;
			break;
		}
	}
	if (infoID == EINF_INVALID) {
		std::cout << "Didn't find Info: '" << infoName << "'" << std::endl;
		std::cout << "Available infos: ";
		for (int i = 0; i < EINFOS; i++) {
			std::cout << EmployeeInfoNames[i] << " ";
		}
		std::cout << std::endl;
		return true;
	}

	// Employee list size
	int size = (int)Employees.size();

	// We'll store the indexes in filtered order to this vector.
	std::vector <int> filteredEmps;
	// Fill it
	for (int i = 0; i < size; i++) {
		filteredEmps.push_back(i);
	}

	std::cout << " ID    | Name                    | Username          | " << infoName << std::endl;
	std::cout << "==============================================================================" << std::endl;

	// Bubble sort

	// buffers
	std::string infoValue;
	std::string infoValue2;
	int smallestloc = 0;
	//int times = 0;
	for (int i = 0; i < size; i++) {
		bool swapped = false;
		for (int i = smallestloc; i < size-1; i++) {
			int loc = filteredEmps[i];
			int loc2 = filteredEmps[i+1];
			infoValue = Employees[loc].GetInfo(infoID);
			infoValue2 = Employees[loc2].GetInfo(infoID);
			int curChar = 0;
			while (true) {
				//times++; // for debugging
				// If the character is the same
				if (infoValue[curChar] == infoValue2[curChar]) {
					curChar++;
					// Check if we run out of chars to compare.
					if (curChar > (int)infoValue.length() || curChar > (int)infoValue2.length()) {
						break;
					}
					continue;
				}
				// Check if we need to swap the employees.
				else if (infoValue[curChar] > infoValue2[curChar]) {
					swapped = true;
					filteredEmps[i] = loc2;
					filteredEmps[i + 1] = loc;
				}
				break;
			}
			
			
		}
		if (!swapped) break;
	}
	//std::cout << "DEBUG: times: " << times << std::endl;
	// Print cycle
	for (int i = 0; i < (int)Employees.size(); i++) {
		int x = filteredEmps[i];
		if (!Employees[x].IsRemoved()) {
			std::string temp;
			std::stringstream spaces;

			temp = " [" + std::to_string(Employees[x].GetID()) + "] "; // Format id column.
			for (int i = 9 - temp.length(); i > 0; i--) spaces << " "; // Calculate the number of spaces we need to add.
			std::cout << temp << spaces.str(); // Print the ID with the spaces
			// Reset and clear space string
			spaces.str(std::string());
			spaces.clear();

			temp = Employees[x].GetInfo(EINF_FIRSTNAME) + " " + Employees[x].GetInfo(EINF_LASTNAME);  // Format name column.
			for (int i = 26 - temp.length(); i > 0; i--) spaces << " "; // Calculate the number of spaces we need to add.
			std::cout << temp << spaces.str(); // Print the name with the spaces
			// Reset and clear space string
			spaces.str(std::string());
			spaces.clear();

			temp = Employees[x].GetUsername();  // Format username column.
			for (int i = 20 - temp.length(); i > 0; i--) spaces << " "; // Calculate the number of spaces we need to add.
			std::cout << temp << spaces.str(); // Print the name with the spaces

			std::cout << Employees[x].GetInfo(infoID) << std::endl; // Print the last info. Since nothing will come after this, we don't need to calculate the spaces.

		}
	}

	return true;
}
bool EmployeeList::ConCmd_Create(cmdArgs Args)
{
	// Get arguments
	std::string Firstname = Args[0];
	std::string Lastname = Args[1];

	Employee newEmployee(Firstname, Lastname);
	AddEmployee(newEmployee);
	std::cout << "Employee added successfully!" << std::endl;

	return true;
}
bool EmployeeList::ConCmd_CreateUser(cmdArgs Args)
{
	// Get arguments
	int userid = atoi(Args[0].c_str()); 

	std::string Username, Password;

	// Check if Employee with such id exist.
	Employee* TempEmp = GetEmployeeByID(userid);
	if (TempEmp == nullptr) { 
		std::cout << "Didn't find Employee with ID: " << userid << std::endl;
		return true;
	}
	// Check if user already has an account.
	if (TempEmp->GetPermission(PERM_USER)) {
		std::cout << "Employee with ID " << userid << " already has an account!" << std::endl;
		return true;
	}
	// Ask for Employee's username.
	bool bIsUnique;
	do {
		bIsUnique = true;
		std::cout << "Enter Employee's Unique Username: ";
		getline(std::cin, Username);
		ConsoleController::replaceAll(Username, "\"", "");

		// Check if no other Employee has such username.
		for (auto &it : Employees) {
			if (it.GetUsername().compare(Username) == 0) {
				bIsUnique = false;
				std::cout << "Entered username is already in use! Try Again..." << std::endl;
				break;
			}
		}

	} while (!bIsUnique); // If Username was not unique, ask again

	// Ask for Employee's password.
	while (true) {
		std::cout << "Enter Employee's Password: ";
		Password = ConsoleController::hidecin(); // Use hidecin to not show the password.

		// Check if password is the right length
		if (Password.size() < 6 || Password.size() > 20) {
			std::cout << "Password must be 6 to 20 characters long! Try Again..." << std::endl;
		}
		else break;
	}

	// Create the account.
	TempEmp->CreateAccount(Username, Password, PERM_DEFAULT );

	std::cout << "Employee account created successfully!" << std::endl;
	return true;
}
bool EmployeeList::ConCmd_GetInfo(cmdArgs Args)
{
	int userid = atoi(Args[0].c_str());
	std::cout << "Employee ID " << userid << " info" << std::endl;
	std::cout << "=============================" << std::endl;
	if (IsValidID(userid)) {
		for (int i = 0; i < EINFOS; i++) {
			std::cout << EmployeeInfoNames[i] << ": " << GetEmployeeInfo(userid, (EInfo)i) << std::endl;
		}
	}
	else {
		std::cout << "No such user found." <<std::endl;
	}
	std::cout << "=============================" << std::endl;
	return true;
}
bool EmployeeList::ConCmd_SetInfo(cmdArgs Args)
{

	int userid = std::stoi(Args[0]);
	std::string infoName = Args[1];
	std::string newValue = Args[2];

	// Change entered info name to lowercase.
	std::transform(infoName.begin(), infoName.end(), infoName.begin(), tolower);


	EInfo infoID = EINF_INVALID;
	for (int i = 0; i < EINFOS; i++) {
		if (EmployeeInfoNames[i].compare(infoName) == 0) {
			infoID = (EInfo)i;
			break;
		}
	}
	if (infoID == EINF_INVALID) {
		std::cout << "Didn't find Info: '" << infoName << "'" <<  std::endl;
		std::cout << "Available infos: ";
		for (int i = 0; i < EINFOS; i++) {
			std::cout << EmployeeInfoNames[i] << " ";
		}
		std::cout << std::endl;
		return true;
	}
	if (SetEmployeeInfo(userid, infoID, newValue)) {
		std::cout << "Successfully changed Employee's info! " << std::endl;
	}
	else
		std::cout << "Didn't find Employee with ID: " << userid << std::endl;

	return true;
}
bool EmployeeList::ConCmd_ListPerms(cmdArgs Args) 
{
	// Get arguments
	int id = atoi(Args[0].c_str());
	
	// Check if Employee with such id exist.
	Employee* TempEmp = GetEmployeeByID(id);
	if (TempEmp == nullptr) {
		std::cout << "Didn't find Employee with ID: " << id << std::endl;
		return true;
	}
	else if (!TempEmp->GetPermission(PERM_USER)) {
		std::cout << "Employee with ID " << id << " does not have an account!" << std::endl;
		return true;
	}
	std::cout << " Employee " << TempEmp->GetInfo(EINF_FIRSTNAME) << " " << TempEmp->GetInfo(EINF_LASTNAME) << " has following permissions" << std::endl;
	std::cout << "================================================" << std::endl;
	for (int i = 0; i < PERMS; i++) {
		if (TempEmp->GetPermission(1 << i)) {
			std::cout << " " << PermNames[i] << std::endl;
		}
	}
	std::cout << "================================================" << std::endl;
	return true;
}
bool EmployeeList::ConCmd_ModifyPerms(cmdArgs Args)
{
	// Get arguments
	int id = atoi(Args[0].c_str());

	// Check if Employee with such id exist.
	Employee* TempEmp = GetEmployeeByID(id);
	if (TempEmp == nullptr) {
		std::cout << "Didn't find Employee with ID: " << id << std::endl;
		return true;
	}
	else if (!TempEmp->GetPermission(PERM_USER)) {
		std::cout << "Employee with ID " << id << " does not have an account!" << std::endl;
		return true;
	}

	while (true) {
		std::cout << "================================================" << std::endl;
		std::cout << " Employee " << TempEmp->GetInfo(EINF_FIRSTNAME) << " " << TempEmp->GetInfo(EINF_LASTNAME) << " permissions" << std::endl;
		std::cout << "================================================" << std::endl;
		std::cout << " Enter the permission number you want to toggle." << std::endl;
		std::cout << " Type 0 to leave." << std::endl;
		std::cout << "================================================" << std::endl;
		for (int i = 0; i < PERMS; i++) {
			if (TempEmp->GetPermission(1 << i)) {
				std::cout << " [" << i + 1 << "] " << PermNames[i] << " [X] ";
			}
			else {
				std::cout << " [" << i + 1 << "] " << PermNames[i] << " [ ] " ;
			}
			// If permission is locked.
			if ( PERMS_BLOCKED & (1 << i) ) {
				std::cout << "- Locked";
			}
			std::cout << std::endl;
			
		}
		std::cout << "================================================" << std::endl;
		std::cout << "Permission to toggle: ";

	
		// Ask permision number
		int x = ConsoleController::cinnum() - 1 ;
	
		if (x < 0) {// If user wants to leave
			return true;
		}
		if (x >= PERMS) { // If user entered a number that doesn't correspond to any permission
			std::cout << "There is no permission with id: " << x << std::endl;
		}
		else {
			// Check if user is trying to remove locked cvar
			if (PERMS_BLOCKED & (1 << x)) {
				// Warn the user!
				std::cout << "!!! You are about to change Locked Permission!" << std::endl;
				std::cout << "!!! Doing so may break the system!" << std::endl;
				std::cout << "!!! Do you want to continue?" << std::endl;
				std::cout << "[ Y / N ] : ";
				std::string input;
				std::getline(std::cin, input); // Ask For input
				// Continue when user presses 'y'
				if (input[0] != 'Y' && input[0] != 'y') {
					std::cout << "Returning..." << std::endl;
					continue;
				}
			}
			// Change the permission
			if (TempEmp->GetPermission(1 << x)) {
				TempEmp->RemovePermission(1 << x);
				std::cout << "Removed permission '" << PermNames[x] << "'." << std::endl;
			}
			else {
				TempEmp->AddPermission(1 << x);
				std::cout << "Added permission '" << PermNames[x] << "'." << std::endl;
			}
		}
	}


	return true;
}
bool EmployeeList::ConCmd_ModifyPassword(cmdArgs Args) {

	std::string Password, ReTypedPass;
	int userid = MainController::GetLoggedInUserID();
	Employee* Emp = GetEmployeeByID(userid);
	while (true) { // Ask for old password
		std::cout << "Enter your old password: ";
		Password = ConsoleController::hidecin(); // Use hidecin to not show the password.
		
		if ( Password[0] == '\0' ) { // If it's empty then cancel password changing
			std::cout << "Password change cancelled!" << std::endl;
			return true;
		}
		else if ( !Emp->CheckPassword(Password) ) { // If old password is invalid
			std::cout << "Invalid password! Please Try Again..." << std::endl;
			continue;
		}
		break;
	}

	while (true) { // Ask for new password
		std::cout << "Enter new password: ";
		Password = ConsoleController::hidecin(); // Use hidecin to not show the password.
												 // Check if password is the right length
		if (Password.size() < 6 || Password.size() > 20) {
			std::cout << "Password must be 6 to 20 characters long! Try Again..." << std::endl;
			continue;
		}
		break;
	}

	while (true) { // Ask to retype new password
		std::cout << "Re-enter new password: ";
		ReTypedPass = ConsoleController::hidecin(); // Use hidecin to not show the password.
												 // Check if password is the right length
		if (ReTypedPass[0] == '\0') { // If it's empty then cancel password changing
			std::cout << "Password change cancelled!" << std::endl;
			return true;
		}
		else if (Password != ReTypedPass) { // If re-Entered password is invalid
			std::cout << "Invalid password! Please Try Again..." << std::endl;
			continue;
		}
		else { // If passwords matched
			Emp->SetPassword(Password); // Update password
			std::cout << "Password changed successfully!" << std::endl;
			return true;
		}
	}
}
void EmployeeList::ConCmd_CreateRoot() 
{
	std::string Firstname, Lastname, Username, Password;
	std::cout << "Enter Employee's First name: ";
	getline(std::cin, Firstname);
	ConsoleController::replaceAll(Firstname, "\"", "");
	std::cout << "Enter Employee's Last name: ";
	getline(std::cin, Lastname);
	ConsoleController::replaceAll(Lastname, "\"", "");
	std::cout << "Enter Employee's Unique Username: ";
	getline(std::cin, Username);
	ConsoleController::replaceAll(Username, "\"", "");
	while (true) {
		std::cout << "Enter Employee's Password: ";
		Password = ConsoleController::hidecin();
		if (Password.size() < 6 || Password.size() > 20) {
			std::cout << "Password must be 6 to 20 characters long! Try Again..." << std::endl;
		}
		else break;
	}
	Employee newEmployee(Firstname, Lastname);
	newEmployee.CreateAccount(Username, Password, PERM_ROOT);
	AddEmployee(newEmployee);
}


EmployeeList::EmployeeList()
{
	using namespace std::placeholders; // for `_1` placeholder
	
	//ConsoleController::RegisterCommand("load", 0, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_Load, this, _1), "Loads all Employees from file.");
	ConsoleController::RegisterCommand("save", 0, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_Save, this, _1), "Saves all Employees to file.");
	ConsoleController::RegisterCommand("list", 0, PERM_VIEWUSERS, std::bind(&EmployeeList::ConCmd_List, this, _1), "Prints a list that contains all Employees.");
	ConsoleController::RegisterCommand("listsort", 1, PERM_VIEWUSERS, std::bind(&EmployeeList::ConCmd_ListSort, this, _1), "Params: <Info name to sort by> | Prints a sorted list that contains all Employees.");
	ConsoleController::RegisterCommand("remove", 1, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_Remove, this, _1), "Params: <UserID> | Remove Employee with specific UserID.");
	ConsoleController::RegisterCommand("adduser", 1, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_CreateUser, this, _1), "Params: <UserID> | Create an Account for an employee.");
	ConsoleController::RegisterCommand("addemployee", 2, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_Create, this, _1), "Params: <First name> <Last name> | Create a new Employee.");
	ConsoleController::RegisterCommand("getinfo", 1, PERM_VIEWUSERS, std::bind(&EmployeeList::ConCmd_GetInfo, this, _1), "Params: <UserID> | Get Employee data.");
	ConsoleController::RegisterCommand("setinfo", 3, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_SetInfo, this, _1), "Params: <UserID> <Info name> <new value> | Set Employee data.");
	ConsoleController::RegisterCommand("listperms", 1, PERM_ADMIN, std::bind(&EmployeeList::ConCmd_ListPerms, this, _1), "Params: <UserID> | List all the permissions employee has.");
	ConsoleController::RegisterCommand("modeperms", 1, PERM_ADMIN, std::bind(&EmployeeList::ConCmd_ModifyPerms, this, _1), "Params: <UserID> | Modify employee permissions.");
	ConsoleController::RegisterCommand("changepw", 0, PERM_USER, std::bind(&EmployeeList::ConCmd_ModifyPassword, this, _1), "Change your password.");
}