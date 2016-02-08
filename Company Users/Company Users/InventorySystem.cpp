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
bool Inventory::removeDevice(int Device_ID) {
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
		float setPrice = atof(szprice.c_str());
		// If the loaded device had bigger id than newid then we need to increase the newid
		// because we don't want to set this same id to any other device we might create later
		curid = newid++;


		// Create new device and push it to list
		deviceList.push_back(Device(name, curid, model_ID, user_ID, location, setPrice, buyDate, description));
	}

	cout << "Devices successfully loaded!" << endl;
	File.close();

}
//==================================================================================================================//
void Inventory::saveDevices() {

	{
		ofstream File("Inventory.db");
		//cout << deviceList.size(); // <- this shows how many lines are in the inventory.db file
		for (int i = 0; i < (int)deviceList.size(); i++) {
			File << deviceList[i].getName() << ", ";
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

	string name, location, newPrice, buyDate, description, newMdlId, newUserId, newSetPrice;

	//Instead of letting user to choose the id, we'll add it automatically
	//And increase the newid so the next device would not get the same id.
	//device_ID = newid++;
	
	cout << "Enter device name: ";
	getline(cin, name);
	cout << "Add model ID: ";
	getline(cin, newMdlId);
	cout << "Add user ID: ";
	getline(cin, newUserId);
	cout << "Add location: ";
	getline(cin, location);
	cout << "Add purchase price: ";
	getline(cin, newPrice);
	cout << "Add purchase date: ";
	getline(cin, buyDate);
	cout << "Add device description: ";
	getline(cin, description);

	int device_ID = newid++; // set unique device_ID
	int	model_ID = atoi(newMdlId.c_str()); // make model_ID to int
	int	user_ID = atoi(newUserId.c_str()); // make user_ID to int
	float setPrice = atof(newSetPrice.c_str()); //make setPrice to float

	// Create new device and push it to list
	deviceList.push_back(Device(name, device_ID, model_ID, user_ID, location, setPrice, buyDate, description));
	// Save devices
	saveDevices();
}
//==================================================================================================================// - Made by Marvin
void Inventory::showDevices() {
	cout << "  ID     Name " << endl;
	cout << "============================ " << endl;
	for (int i = 0; i < (int)deviceList.size(); i++) {
		cout << " [" << deviceList[i].getDevice_ID() << "] - " << deviceList[i].getName() << endl;
	}
	cout << "============================ " << endl << endl;
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

		if (input == "1") { addDevice(); }
		else if (input == "2") { /*changeDevice();*/ }
		else if (input == "3") { /*bool removeDevice(int Device_ID);*/ }
		else if (input == "4") { showDevices(); }
		else if (input == "5") { /*showModelDevices();*/ }
		else if (input == "6") { /*totalValue();*/ }
		else if (input == "7") { return true; }
		else { cout << "Incorrect input!" << endl; }
	}
	return true;
}