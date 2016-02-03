#include "stdafx.h"
#include "ConsoleController.h"

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
void ConsoleController::CommandHandler(EmployeeList * EmpList, MainController * LoginSys)
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
		input = arguments[0]; // Set the input to only include command
		arguments.erase(arguments.begin()); // Remove the command from argument list

		// Check commands
		if (input.compare("exit") == 0) {
			return;
		}
		else if (input.compare("help") == 0) {
			std::cout << "===== Help =====" << std::endl;
			for (auto &it : CommandList) {
				std::cout << " " << it.commandName << " - " << it.commandDesc << std::endl;
			}
			std::cout << "================" << std::endl;
		}
		else if (input.compare("login") == 0) {
			if (!LoginSys->IsLoggedIn()) {
				std::string Username, Password;
				std::cout << "Enter your username: ";
				getline(std::cin, Username);
				std::cout << "Enter your password: ";
				getline(std::cin, Password);

				int retval = LoginSys->LogIn(Username, Password, EmpList);
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
		else if (LoginSys->IsLoggedIn()) {
			bool bSuccess = false;
			for (auto &it : CommandList) {
				if (it.commandName.compare(input) == 0) {
					if (EmpList->GetEmployeeByID(LoginSys->GetLoggedInUserID())->GetPermission(it.reqPerms)) {// Check if user has permissions to do this.
						if (it.argNum == argnum) { // Check if user entered the right amount of arguments.
							it.callbackFnc(arguments);
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
int ConsoleController::cinnum()
{
	int x;
	while (!(std::cin >> x)) {
		cinreset();
		std::cout << "You didn't enter a number! please try again: ";
	}
	return x;
}
void ConsoleController::cinreset()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
