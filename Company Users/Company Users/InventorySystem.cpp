//INVENTORY SYSTEM CPP//
/*==================================================================================================================//
Made by: Karl Robert Lillipuu & Kevin Jasson(a little bit)
People who helped(many thanks!): Lauri Mäe, Marvin Helstein, Samael Tamm
//==================================================================================================================*/
/*==================================================================================================================//

Changelog:

- Version 0.1|02.02.2016| - prints main menu and can add devices.
- Version 0.2|09.02.2016| - now works remove device, view total inventory value, view devices.
- Version 1.0|15.02.2016| - Basicly done, bug fixes(might still have some).
- Version 1.1|18.02.2016| - Huge commenting and instructions.
/*===================================================================================================================/
INSTRUCTIONS - here is comments how inventory system works
			 - write: "inventory" to get access to inventory functions -> prints inventory functions
			 - Inventory function:
				* loadDevices(); - loads saved devices in file called inventory.db
				* saveDevices(); - used for saving devices information
				* addDevice(); -  used for adding device(name,device_id, model_id, user_id, location, price, date, description)
				* removeDevice(); - used to remove specific device 
				* changeDevice(); - used to change specific devices information(name, model_id etc)
				* showDevices(); -  used to see all devices(and their device_id)
				* showModelDevice(); -  shows devices model_ID and names
				* totalValue(); -  used to see inventory(devices) total value
				* deviceInfo(); - used to see specific device information
			 - Enter "0" to leave from inventory system
			 - More comments in the code below
//==================================================================================================================//
/*==================================================================================================================//
COMMENT BOX - comment here if any bugs found or any ideas to make system better
			 - 
			 -
			 -
			 -
//==================================================================================================================*/
#include "stdafx.h"
#include "InventorySystem.h"
#include "EmployeeList.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;
// Constructor
Inventory::Inventory(EmployeeList* newEmpList) {
	newid = 0; // We will start from the id 0.

	EmpList = newEmpList;

	//Register commands
	using namespace std::placeholders; // for `_1` placeholder
	ConsoleController::RegisterCommand("inventory", 0, PERM_MODIFYINVENTORY, std::bind(&Inventory::ConCmd_Menu, this, _1), "Enter the inventory system.");

	//Load inventory.
	loadDevices();
}
//==================================================================================================================//
void Inventory::loadDevices() {
	ifstream File("Inventory.db"); //change later to devices.db file

	string record;
	while (getline(File, record)) {
		istringstream ss(record);
		int curid = 0;
		string field, name, location, szprice, buyDate, description, szuser, szdevice, szmodel;

		getline(ss, field, ','); name = field;
		getline(ss, field, ','); szuser = field;
		getline(ss, field, ','); szmodel = field;
		getline(ss, field, ','); location = field;
		getline(ss, field, ','); szprice = field;
		getline(ss, field, ','); buyDate = field;
		getline(ss, field, ','); description = field;
		int	model_ID = atoi(szmodel.c_str());
		int	user_ID = atoi(szuser.c_str());
		float setPrice = (float)atof(szprice.c_str());
		// If the loaded device had bigger id than newid then we need to increase the newid
		// because we don't want to set this same id to any other device we might create later
		curid = newid++;

		// Create new device and push it to list
		deviceList.push_back(Device(name, curid, model_ID, user_ID, location, setPrice, buyDate, description));
	}
	//when devices are loaded successfully
	
	File.close();

}
//==================================================================================================================//
void Inventory::saveDevices() {

	{
		//saves Device information and puts commas between information data
		ofstream File("Inventory.db");
		//cout << deviceList.size(); // <- this shows how many lines are in the inventory.db file
		for (int i = 0; i < (int)deviceList.size(); i++) {
			File << deviceList[i].getName() << ", ";
			File << deviceList[i].getModel_ID() << ", ";
			File << deviceList[i].getUser_ID() << ", ";
			File << deviceList[i].getLocation() << ", ";
			File << deviceList[i].getPrice() << ", ";
			File << deviceList[i].getDate() << ",";
			File << deviceList[i].getDescription() << "\n";
		}
		File.close();
	}
}
//==================================================================================================================//
void Inventory::addDevice() {

	//declarations
	string name, location, buyDate, description;
	int newModelId, newUserId; 
	float newPrice;

	//user enters Device information
	cout << "Enter device name: ";
	getline(cin, name);
	cout << "Add model ID: ";
	newModelId = ConsoleController::cinnum();
	while (true) {
		cout << "Add user ID: ";
		newUserId = ConsoleController::cinnum();
		if (newUserId == -1)
		{
			return;
		}
		if (!EmpList->IsValidID(newUserId))
		{
			cout << "Invalid User ID: " << newUserId << endl;
			cout << "Try Again, or write -1 to cancel." << endl;
			continue;
		}
		break;
	}
	

	cout << "Add location: ";
	getline(cin, location);
	cout << "Add purchase price: ";
	newPrice = ConsoleController::cinfloat();
	cout << "Add purchase date (DD.MM.YY): ";
	getline(cin, buyDate);
	cout << "Add device description: ";
	getline(cin, description);

	int device_ID = newid++; // set unique device_ID
												
	// Create new device and push it to list
	deviceList.push_back(Device(name, device_ID, newModelId, newUserId, location, newPrice, buyDate, description));

	cout << "Device added successfully!" << endl;
	// Save devices
	saveDevices();
}
//==================================================================================================================//
void Inventory::changeDevice() {
	//prints  devices
	showDevices();

	int device_ID;
	//user enters device_ID what he/she wants to change/modify
	cout << "Select device you want to change: ";
	device_ID = ConsoleController::cinnum();

	//information menu
	for (int i = 0; i < (int)deviceList.size(); i++) {
		if (deviceList[i].getDevice_ID() == device_ID) { //this should loop trough devicelist and get the correct ID
			string data;
			cout << "============================ " << endl;
			cout << "[1]Name" << endl;
			cout << "[2]Model_ID" << endl;
			cout << "[3]User_ID" << endl;
			cout << "[4]Location" << endl;
			cout << "[5]Purchase Price" << endl;
			cout << "[6]Purchase Date" << endl;
			cout << "[7]Description" << endl;
			cout << "[0]exit" << endl;
			cout << "============================ " << endl;
			cout << "Choose what to change: ";

			//user selects what he/she wants to change
			getline(cin, data);
			if (data == "1") deviceList[device_ID].setName();
			else if (data == "2") deviceList[device_ID].setModel_ID();
			else if (data == "3") deviceList[device_ID].setUser_ID();
			else if (data == "4") deviceList[device_ID].setLocation();
			else if (data == "5") deviceList[device_ID].setPrice();
			else if (data == "6") deviceList[device_ID].setDate();
			else if (data == "7") deviceList[device_ID].setDescription();
			else if (data == "0") return;
			else {
				cout << "Wrong input!" << endl; 
				return; 
			}
			}
			}
		}
//==================================================================================================================//
void Inventory::removeDevice() {

	int device_ID;
	string buf;
	showDevices(); // displays devices


	cout << "Enter device_ID you want to remove: "; // user enters device_ID
	getline(cin, buf);
	device_ID = atoi(buf.c_str());

	string sure;
	cout << "Are you sure?" << endl; //asks if user is sure to delete device
	cout << "[1]Yes." << endl;
	cout << "[2]No." << endl;
	getline(cin, sure);

	if (sure == "1"){ //when user wants to delete device
		// Loop through all devices
		for (int i = 0; i < (int)deviceList.size(); i++) {
			// Check if we got a correct one
			if (deviceList[i].getDevice_ID() == device_ID) {
				// If we did erase it and return true.
				deviceList.erase(deviceList.begin() + i);

				cout << "============================ " << endl;
				cout << "Device is removed!" << endl;
				cout << "============================ " << endl;
			}
		}
		saveDevices(); // saves devices
	}
	else if (sure == "2"){
		return;
	}
	else { //when user enters wrong input
		cout << "Wrong input!" << endl;
	}
}
//==================================================================================================================//
void Inventory::showDevices() {
	cout << "  ID     Name " << endl;
	cout << "============================ " << endl;
	for (int i = 0; i < (int)deviceList.size(); i++) { //(int)deviceList.size();
		cout << " [" << deviceList[i].getDevice_ID() << "] - " << deviceList[i].getName() << endl; //displays device ID and device name
	}
	cout << "============================ " << endl << endl;
}
//==================================================================================================================//
void Inventory::showModelDevices() {

	//sort devices by model ID

	cout << "  Model ID     Name " << endl;
	cout << "============================ " << endl;
	for (int i = 0; i < (int)deviceList.size(); i++) { //(int)deviceList.size();
		cout << " [" << deviceList[i].getModel_ID() << "] - " << deviceList[i].getName() << endl; //displays device ID and device name
	}
	cout << "============================ " << endl;

}
//==================================================================================================================//
void Inventory::totalValue() {

	float inventoryValue = 0; // sets inv value to 0

	for (int i = 0; i < (int)deviceList.size(); i++) { //loops through so many times how many devices there is
		if (deviceList[i].getPrice()) { //when price is found
			inventoryValue += deviceList[i].getPrice(); //adds devices value to inventory Value
		}
	}
	cout << "============================ " << endl;
	cout << inventoryValue << " - Euros" << endl;
	cout << "============================ " << endl;

}
//==================================================================================================================//
void Inventory::deviceInfo() {
	//this function shows specific device information
	//user chooses device
	//console prints chosen device info

	int device_ID = 0;
	string buf;
	showDevices(); // displays devices


	cout << "Enter device_ID to see device information: "; // user enters device_ID
	getline(cin, buf);
	device_ID = atoi(buf.c_str());


	//for (device_ID = 0; device_ID < deviceList.size(); device_ID++;) { //(int)deviceList.size(); //This is not actually needed, and why did you put device ID to 0? '-'
		for (int i = 0; i < (int)deviceList.size(); i++) {
			if (deviceList[i].getDevice_ID() == device_ID) { // If my brain data is 100% correct, this should loop trough devicelist and get the correct ID without printing all. ok
				cout << "============================ " << endl;
				cout << "Device name: " << deviceList[device_ID].getName() << endl;
				cout << "Device model ID : " << deviceList[device_ID].getModel_ID() << endl;
				cout << "Device user ID : " << deviceList[device_ID].getUser_ID() << endl;
				cout << "Device location: " << deviceList[device_ID].getLocation() << endl;
				cout << "Device purchase price: " << deviceList[device_ID].getPrice() << endl;
				cout << "Device purchase date: " << deviceList[device_ID].getDate() << endl;
				cout << "Device description: " << deviceList[device_ID].getDescription() << endl;
				cout << "============================ " << endl;
			}
		}
}
//==================================================================================================================//
void Inventory::saveChanges() {

	string sure;
	while (true) {
		cout << "Do you want to save changes?" << endl; //asks if user is sure to delete device
		cout << "[1]Yes." << endl;
		cout << "[2]No." << endl;
		getline(cin, sure);
		if (sure == "1") {
			cout << "Device changes saved!" << endl;
			saveDevices();
			return;
		}
		else if (sure == "2") {
			cout << "Device changes not saved!" << endl;
			return;
		}
		else {
			cout << "============================" << endl;
			cout << "Wrong input! You Typed: " << sure << endl;
			cout << "Try again!" << endl;
			continue;
		}
		break;
	}

}
//==================================================================================================================//
bool Inventory::ConCmd_Menu(cmdArgs Args) {

	//function names says all what the function does

	while (true) {
		string input; // user option
		cout << "============================ " << endl;
		cout << "[1]Add device" << endl; //addDevice();
		cout << "[2]Change device" << endl; //changeDevice();
		cout << "[3]Remove device" << endl; //removeDevice();
		cout << "[4]Inventory overview" << endl;  //showDevices();
		cout << "[5]Model-based overview" << endl; //showModelDevices();
		cout << "[6]Inventory total value" << endl; //totalValue();
		cout << "[7]Print specific device info" << endl; //deviceInfo();
		cout << "[0]Leave inventory system" << endl; //leaves the system
		cout << "============================ " << endl;
		cout << "Choose action: ";
		getline(cin, input); // user enters the action

		if (input == "1") { addDevice(); }
		else if (input == "2") { changeDevice(); }
		else if (input == "3") { removeDevice(); }
		else if (input == "4") { showDevices(); }
		else if (input == "5") { showModelDevices(); }
		else if (input == "6") { totalValue(); }
		else if (input == "7") { deviceInfo(); }
		else if (input == "0") { saveChanges(); return true; }
		else { cout << "\"" << input << "\"" << " is incorrect input!" << endl; } // when user enters unknown input
	}
	return true;
}
//==================================================================================================================//