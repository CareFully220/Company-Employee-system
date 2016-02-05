/*
==========================================================================
Inventory 0.1 - can calculate grades, avarage grades, shape girths and areas
Copyright (C) 2016 Karl Robert Lillipuu

This program iSs free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
==========================================================================
==========
Changelog:
==========
- Version 0.1|02.02.2016| - prints main menu and can add devices

*/
#include "stdafx.h"
#include "InventorySystem.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;

// Constructor
Inventory::Inventory() { 
	newid = 0; // We will start from the id 0.

	// Register commands
	using namespace std::placeholders; // for `_1` placeholder
	ConsoleController::RegisterCommand("inventory", 0, PERM_MODIFYINVENTORY, std::bind(&Inventory::ConCmd_Menu, this, _1), "Enter the inventory system.");

	// Load inventory.
	loadDevices(); 
}
//==================================================================================================================//
bool Inventory::removeDevice(string Device_ID) {
	// Loop through all devices
	for (int i = 0; i < (int)deviceList.size(); i++) { 
		// Check if we got a correct one
		if (deviceList[i].getDevice_ID() == Device_ID) { 
			// If we did erase it and return true.
			deviceList.erase(deviceList.begin() + i);
			return true;
		}
	}
	// If we didn't find device with specified id.
	return false;
}
//==================================================================================================================//
void Inventory::loadDevices() {
	ifstream File("Inventory.db"); //change later to devices.db file


	string record;
	while (getline(File, record)) {
		istringstream ss(record);
		string field, name, device_ID, model_ID, user_ID, location, setPrice, buyDate, description;
		getline(ss, field, ','); name = field;
		getline(ss, field, ','); user_ID = field;
		getline(ss, field, ','); device_ID = field;
		getline(ss, field, ','); model_ID = field;
		getline(ss, field, ','); location = field;
		getline(ss, field, ','); setPrice = field;
		getline(ss, field, ','); buyDate = field;
		getline(ss, field, ','); description = field;
		
	}

	cout << "Device successfully added!" << endl;
	File.close();

}
//==================================================================================================================//
void Inventory::saveDevices() {

	{
		ofstream File("Inventory.db");
		//cout << deviceList.size(); // <- this shows how many lines are in the info.txt file
		for (int i = 0; i < (int)deviceList.size(); i++) {
			File << deviceList[i].getName() << ", ";
			File << deviceList[i].getDevice_ID() << ", ";
			File << deviceList[i].getModel_ID() << ", ";
			File << deviceList[i].getUser_ID() << ", ";
			File << deviceList[i].getLocation() << ", ";
			File << deviceList[i].getDescription() << ", ";
			File << deviceList[i].getPrice() << ", ";
			File << deviceList[i].setDate() << "\n";
		}
		File.close();
	}
}

//==================================================================================================================//
void Inventory::addDevice() {

	string name, device_ID, model_ID, user_ID, location, setPrice, buyDate, description;

	cout << "Enter device name: ";
	getline(cin, name);
	cout << "Add device ID: ";
	getline(cin, device_ID);
	cout << "Add model ID: ";
	getline(cin, model_ID);
	cout << "Add user ID: ";
	getline(cin, user_ID);
	cout << "Add location: ";
	getline(cin, location);
	cout << "Add purchase price: ";
	getline(cin, setPrice);
	cout << "Add purchase date: ";
	getline(cin, buyDate);
	cout << "Add device description: ";
	getline(cin, description);

	// Create new device and push it to list
	deviceList.push_back(Device(name, device_ID, model_ID, user_ID, location, setPrice, buyDate, description));
	// Save devices
	saveDevices();
}
//==================================================================================================================//
bool Inventory::ConCmd_Menu(cmdArgs Args) {

	while (true) {
		string input; // user option

		cout << "[1]Add device" << endl; //addDevice();
		cout << "[2]Change device" << endl; //changeDevice();
		cout << "[3]Remove device" << endl; //removeDevice();
		cout << "[4]Inventory overview" << endl;  //showDevices();
		cout << "[5]Model-based overview" << endl; //showModelDevices();
		cout << "[6]Inventory total value" << endl; //totalValue();
		cout << "[7]Leave inventory system" << endl;
		cout << "Choose action: ";
		getline(cin, input); // user enters the action

		if (input == "1") {
			addDevice();
		}
		else if (input == "6") {
			//cout << buyPrice << endl;
		}
		else if (input == "7") {
			return true;
		}
		else {
			cout << "lol" << endl;
		}
	}
	return true;
}