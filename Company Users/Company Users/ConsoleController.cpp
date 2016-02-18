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
#include "ConsoleController.h"
#undef max
/*ConsoleController::ConsoleController() :
	Logsys(this)
{

}*/
std::vector <Command> ConsoleController::CommandList;

void ConsoleController::PrintWelcomeMessage() 
{
	std::cout << "=== Company Employee System Command Line Interface. ===" << std::endl;
	std::cout << " Type 'help' to see a list of available commands." << std::endl;
	std::cout << " Before you can do anything, you need to 'login'." << std::endl;
}
void ConsoleController::CommandHandler(EmployeeList& EmpList)
{
	// Ask for command
	while (true) {
		std::string input;
		std::cout << "> ";
		//cinreset();
		std::getline(std::cin, input); // Ask For input

		// Filter out the arguments and command
		// Temporary variables:
		std::stringstream ssinput;
		ssinput << input;
		std::string temp;

		cmdArgs arguments; // Argument list.
		int argnum = -1; // Number of arguments inputted. It is -1, because it will also include command, but we don't want that.
		while (getline(ssinput, temp, ' ')) { // Get next argument.
			arguments.push_back(temp); // Add it to argument list.
			argnum++; // Increment argument amount number.
		}
		if (arguments.size() == 0) {
			continue;
		}
		input = arguments[0]; // Set the input to only include command
		// Change command to lowercase
		std::transform(input.begin(), input.end(), input.begin(), tolower);

		arguments.erase(arguments.begin()); // Remove the command from argument list

		// Check commands
		if (input.compare("exit") == 0) {
			return;
		}
		else if (input.compare("help") == 0) {
			// Default is page 1
			int page = 1; // current page
			int loc = 0; // current location
			int maxloc = 10; // max commands per page
			int maxpages = ((CommandList.size()-1) / maxloc) + 1; // Max pages
			// If user specified different page.
			if (argnum > 0) {
				int tempPage = atoi(arguments[0].c_str()); // String to number.
				if (tempPage > 1){ // if there is such page
					if (tempPage > maxpages)
						page = maxpages;
					else 
						page = tempPage;
					loc = (page - 1) * 10; // set location to chosen page.
					maxloc = loc + maxloc; // set maximum location to the end of the page.
				}
			}
			std::cout << "===== Help =====" << std::endl;
			std::cout << "Page " << page << " / " << maxpages << std::endl;
			std::cout << "================" << std::endl;
			for (; loc < (int)CommandList.size() && loc < maxloc; loc++) {
			//for (auto &it : CommandList) {
				std::cout << " " << CommandList[loc].commandName << " - " << CommandList[loc].commandDesc << std::endl;
			}
			std::cout << "================" << std::endl;
		}
		else if (input.compare("login") == 0) {
			if (!MainController::IsLoggedIn()) {
				std::string Username, Password;
				std::cout << "Enter your username: ";
				getline(std::cin, Username);
				std::cout << "Enter your password: ";
				Password = hidecin();

				int retval = MainController::LogIn(Username, Password, EmpList);
				if (retval == 1) {
					std::cout << "Log in successful!" << std::endl;
				}
				else if (retval == -1) {
					std::cout << "You have no permissions to log in!" << std::endl;
				}
				else if (retval == -2) {
					std::cout << "Wrong Username or Password!" << std::endl;
				}
			}
			else {
				std::cout << "You are already logged in!" << std::endl;
			}
		}
		else if (MainController::IsLoggedIn()) {
			bool bSuccess = false;
			for (auto &it : CommandList) {
				if (it.commandName.compare(input) == 0) {
					if (EmpList.GetEmployeeByID(MainController::GetLoggedInUserID())->GetPermission(it.reqPerms)) {// Check if user has permissions to do this.
						if (argnum >= it.argNum ) { // Check if user entered the right amount of arguments.
							if (!it.callbackFnc(arguments)) {
								std::cout << "Usage >> " << it.commandDesc << std::endl;
							}
						}
						else {
							std::cerr << "Wrong number of arguments passed!" << std::endl;
							std::cout << "Usage >> " << it.commandDesc << std::endl;
						}
					}
					else {
						std::cerr << "You don't have permission to do this!" << std::endl;
					}
					
					bSuccess = true;
					break;
				}
			}
			if (!bSuccess) {
				std::cout << "Invalid Command '" << input << "'! Type 'help' for a list of available commands." << std::endl;
			}

		
		}
		else {
			std::cout << "You need to 'login' before you can do that!" << std::endl;
		
		}
	}

}

void ConsoleController::RegisterCommand(std::string commandName, int nArguments, int requiredPerms, callback callbackFnc, std::string description)
{
	if (callbackFnc != nullptr){
		if (commandName[0] != '\0') {
			Command newCommand;
			// Make command name lowercase.
			std::transform(commandName.begin(), commandName.end(), commandName.begin(), tolower);
			newCommand.commandName = commandName;
			newCommand.commandDesc = description;
			newCommand.argNum = nArguments < 0 ? 0 : nArguments;
			newCommand.reqPerms = requiredPerms;
			newCommand.callbackFnc = callbackFnc;
			CommandList.push_back(newCommand);
		}
		else {
			std::cerr << "Error registering command!" << std::endl;
		}
	}
	else {
		std::cerr << "Error registering command '" << "' !" << std::endl;
	}
}
int ConsoleController::cinnum() {
	int x;
	while (!(std::cin >> x)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "You did not enter a number. Try again: ";
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return x;
}
float ConsoleController::cinfloat() {
	std::string input;

	float dummy;
	while (std::cin >> input)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::istringstream iss(input);
		
		iss >> std::noskipws >> dummy;
		if (!(iss && iss.eof()))
			std::cerr << "You did not enter a float. Try again: ";
		else
			break;
	}
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return dummy;

}
std::string ConsoleController::hidecin() {
	// Grabbed from http://www.cplusplus.com/forum/general/3570/#msg15410
	// Set the console mode to no-echo, not-line-buffered input
	std::string result;
	DWORD mode, count;
	HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleMode(ih, &mode))
		throw std::runtime_error(
			"You must be connected to a console to use this program.\n"
			);
	SetConsoleMode(ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
	// Get the password string

	char c;
	while (ReadConsoleA(ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
	{
		if (c == '\b')
		{
			if (result.length())
			{
				WriteConsoleA(oh, "\b \b", 3, &count, NULL);
				result.erase(result.end() - 1);
			}
		}
		else
		{
			WriteConsoleA(oh, "*", 1, &count, NULL);
			result.push_back(c);
		}
	}
	// Restore the console mode
	SetConsoleMode(ih, mode);

	std::cout << std::endl;
	return result;
}
int ConsoleController::replaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	int nReplacements = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		nReplacements++;
	}
	return nReplacements;
}