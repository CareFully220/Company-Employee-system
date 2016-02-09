/*
Inventory System cpp
==========
Changelog:
==========
- Version 0.1|02.02.2016| - prints main menu and can add devices
- Version 0.2|09.02.2016| - now works remove device, view total inventory value, view devices.

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
//==================================================================================================================//
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
	//when devices are loaded successfully
	cout << "Devices successfully loaded!" << endl;
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
			File << deviceList[i].setDate() << ",";
			File << deviceList[i].getDescription() << "\n";
		}
		File.close();
	}
}
//==================================================================================================================//
void Inventory::addDevice() {

	string name, location, newPrice, buyDate, description, newMdlId, newUserId; //declarations


	//user enters Device information
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
	float setPrice = atof(newPrice.c_str()); //make setPrice to float

											 // Create new device and push it to list
	deviceList.push_back(Device(name, device_ID, model_ID, user_ID, location, setPrice, buyDate, description));
	// Save devices
	saveDevices();
}
//==================================================================================================================//
void Inventory::changeDevice() {
	//user selects a device by device_ID
	showDevices();

	int device_ID;
	string buf;
	//user enters device_ID what he/she wants to change/modify
	cout << "Select device you want to change: ";
	getline(cin, buf);
	device_ID = atoi(buf.c_str());

	//asks if user is sure to change that device
	string sure;
	cout << "Are you sure?" << endl; //asks if user is sure to delete device
	cout << "[1]Yes." << endl;
	cout << "[2]No." << endl;
	getline(cin, sure);
	//information menu
	string data;

	cout << "[1]Name" << endl;
	cout << "[2]Model_ID" << endl;
	cout << "[3]User_ID" << endl;
	cout << "[4]Location" << endl;
	cout << "[5]Purchase Price" << endl;
	cout << "[6]Purchase Date" << endl;
	getline(cin, data);

	//make loop to the right device
	//go to the data what user want to change
	//erase current data
	//user enters new data


	//here happens the magic
	// I don't know how it works so yeah, It's kinda GG
	//this->deviceList.name = changeName;

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
	for (int i = 0; i < deviceList.size(); i++) { //(int)deviceList.size();
		cout << " [" << deviceList[i].getDevice_ID() << "] - " << deviceList[i].getName() << endl; //displays device ID and device name
	}
	cout << "============================ " << endl << endl;
}
//==================================================================================================================//
void Inventory::showModelDevices() {

	//sort devices by model ID

	cout << "  Model ID     Name " << endl;
	cout << "============================ " << endl;
	for (int i = 0; i < deviceList.size(); i++) { //(int)deviceList.size();
		cout << " [" << deviceList[i].getModel_ID() << "] - " << deviceList[i].getName() << endl; //displays device ID and device name
	}
	cout << "============================ " << endl << endl;

}
//==================================================================================================================//
void Inventory::totalValue() {

	float inventoryValue = 0; // sets inv value to 0

	for (int i = 0; i < deviceList.size(); i++) { //loops through so many times how many devices there is
		if (deviceList[i].getPrice()) { //when price is found
			inventoryValue += deviceList[i].getPrice(); //adds devices value to inventory Value
		}
	}
	cout << "============================ " << endl;
	cout << inventoryValue << " - Euros" << endl;
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
		cout << "[7]Leave inventory system" << endl; //leaves the system
		cout << "Choose action: ";
		getline(cin, input); // user enters the action

		if (input == "1") { addDevice(); }
		else if (input == "2") { changeDevice(); }
		else if (input == "3") { removeDevice(); }
		else if (input == "4") { showDevices(); }
		else if (input == "5") { showModelDevices(); }
		else if (input == "6") { totalValue(); }
		else if (input == "7") { return true; }
		else { cout << "\"" << input << "\"" << " is incorrect input!" << endl; } // when user enters unknown input
	}
	return true;
}
//==================================================================================================================//