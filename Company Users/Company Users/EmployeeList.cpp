#include "stdafx.h"
#include "EmployeeList.h"

bool EmployeeList::LoadEmployees(std::string FileName )
{
	std::ifstream file(FileName); // Open the file for writing

	if (!file.is_open()) return false; // If there is no file open

	std::string szBuffer; // Buffer to store selected line

	std::string UserData[13];
	int iUserData[1];
	while (std::getline(file, szBuffer)) {
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

			iUserData[0] = atoi(UserData[11].c_str());
			AddEmployee(Employee(UserData[0], UserData[1], UserData[2], UserData[3], UserData[4], UserData[5], UserData[6], UserData[7], UserData[8], UserData[9], UserData[10], iUserData[0]));
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
		file << "\"" << it.GetInfo(EINF_FIRSTNAME) << "\" \""
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
bool EmployeeList::RemoveEmployee(int id)
{
	for (auto it = Employees.begin(); it != Employees.end(); it++) {
		if (it->GetID() == id) {
			//Employees.erase(it);
			return true;
		}
	}
	return false;
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

Employee* EmployeeList::GetEmployeeByID(int id) {
	for (int i = 0; i < GetEmployeeCount(); i++) {
		if (Employees[i].GetID() == id) {
			return &Employees[i];
		}
	}
	return nullptr;
}


// Command Callbacks
bool EmployeeList::ConCmd_Load(cmdArgs Args)
{
	return true;
}
bool EmployeeList::ConCmd_Save(cmdArgs Args)
{
	SaveEmployees("EmloyeeData.db");
	std::cout << "Employees saved!" << std::endl;
	return true;
}
bool EmployeeList::ConCmd_Add(cmdArgs Args)
{
	return true;
}
bool EmployeeList::ConCmd_Remove(cmdArgs Args)
{
	int id = atoi(Args[0].c_str());
	if (RemoveEmployee(id)) {
		std::cout << "Sucessfully removed Employee ID: " << id << std::endl;
		return true;
	}
	else {
		std::cout << "Didn't find Employee with ID: " << id << std::endl;
		return true;
	}
}
std::string EmployeeList::GetEmployeeInfo(int id, EInfo InfoID) 
{
	Employee * tempEmp = GetEmployeeByID(id);
	if (tempEmp != nullptr)
		return tempEmp->GetInfo(InfoID);
	else 
		return "";
}
bool EmployeeList::SetEmployeeInfo(int id, EInfo InfoID, std::string newValue)
{
	Employee * tempEmp = GetEmployeeByID(id);
	if (tempEmp != nullptr) {
		tempEmp->SetInfo(InfoID, newValue);
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeList::ConCmd_List(cmdArgs Args)
{
	std::cout << " ID - First Name - Last Name - User Name" << std::endl;
	for (auto &it : Employees) {
		std::cout << "[ " << it.GetID() << " ] " << it.GetInfo(EINF_FIRSTNAME) << " - " << it.GetInfo(EINF_LASTNAME) << " - " << it.GetUsername() << std::endl;
	}
	return true;
}
bool EmployeeList::ConCmd_Create(cmdArgs Args)
{
	std::string Firstname = Args[0];
	std::string Lastname = Args[1];
	std::string Username = Args[2];
	std::string Password = Args[3];

	if (Firstname[0] == '\0' || Lastname[0] == '\0' || Username[0] == '\0') {
		std::cout << "You did not enter required arguments!" << std::endl;
		return false;
	}
	for (auto &it : Employees) {
		if (it.GetUsername().compare(Username) == 0) {
			std::cout << "Given Account Name is already in use!" << std::endl;
			return true;
		}
	}
	if (Password.size() < 6 || Password.size() > 20) {
		std::cout << "Password must be 6 to 20 characters long!" << std::endl;
		return true;
	}

	Employee newEmployee(Firstname, Lastname);
	newEmployee.CreateAccount(Username, Password, PERM_USER | PERM_ALLOWLOGIN);
	AddEmployee(newEmployee);
	return true;
}
bool EmployeeList::ConCmd_GetInfo(cmdArgs Args)
{
	int userid = atoi(Args[0].c_str());
	std::cout << "Employee id " << userid << " info" << std::endl;
	std::cout << "=============================" << std::endl;
	for (int i = 0; i < EINFOS; i++) {
		std::cout << EmployeeInfoNames[i] << ": " << GetEmployeeInfo(userid, (EInfo)i) << std::endl;
	}
	std::cout << "=============================" << std::endl;
	return true;
}
bool EmployeeList::ConCmd_SetInfo(cmdArgs Args)
{
	int userid = atoi(Args[0].c_str());
	std::string infoName = Args[1];
	std::string newValue = Args[2];
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
	if (SetEmployeeInfo(userid, infoID, newValue))
		std::cout << "Successfully changed Employee's info! " << std::endl;
	else
		std::cout << "Didn't find Employee with id: " << userid << std::endl;

	return true;
}
void EmployeeList::ConCmd_CreateRoot() 
{
	std::string Firstname, Lastname, Username, Password;
	std::cout << "Enter Employee's First name: ";
	getline(std::cin, Firstname);
	std::cout << "Enter Employee's Last name: ";
	getline(std::cin, Lastname);
	std::cout << "Enter Employee's Unique Username: ";
	getline(std::cin, Username);
	while (true) {
		std::cout << "Enter Employee's Password: ";
		Password = ConsoleController::hidecin();
		if (Password.size() < 6 || Password.size() > 20) {
			std::cout << "Password must be 6 to 20 characters long! Try Again...";
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
	
	ConsoleController::RegisterCommand("load", 0, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_Load, this, _1), "Loads all Employees from file.");
	ConsoleController::RegisterCommand("save", 0, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_Save, this, _1), "Saves all Employees to file.");
	ConsoleController::RegisterCommand("list", 0, PERM_VIEWUSERS, std::bind(&EmployeeList::ConCmd_List, this, _1), "Prints a list that contains all Employees.");
	ConsoleController::RegisterCommand("remove", 1, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_Remove, this, _1), "Params: <UserID> | Remove Employee with specific UserID.");
	ConsoleController::RegisterCommand("add", 4, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_Create, this, _1), "Params: <Frist name> <Last name> <Username> <Password> | Create a new Employee.");
	ConsoleController::RegisterCommand("getinfo", 1, PERM_VIEWUSERS, std::bind(&EmployeeList::ConCmd_GetInfo, this, _1), "Params: <UserID> | Get Employee data.");
	ConsoleController::RegisterCommand("setinfo", 3, PERM_MODIFYUSERS, std::bind(&EmployeeList::ConCmd_SetInfo, this, _1), "Params: <UserID> <Info name> <new value> | Set Employee data.");
}