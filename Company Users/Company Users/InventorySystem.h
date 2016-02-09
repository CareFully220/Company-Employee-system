/**
* @file InventorySystem.h
* @brief Everything related to Inventory system.
*/

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "ConsoleController.h"
using namespace std;

/* Some notes for you Karl and/or Kevin... and maybe to Lauri?:
	* You should make ID's into intregers.
	* So that i wouldn't change the whole code, I left the menu as it is (only fixed it). 
		If you want you can make all the menu items into commands.
	* I made seperate Inventory Class that controls the devices.
	* You need to make checks where user needs to enter user id for example.
		You need to check if it's valid.
	* I commented the code i wrote as much as i could.

	-- by *CareFully*
*/

//class about device
class Device {
protected:
	string name; // device name
	int device_ID; // device id
	int model_ID; // device model id
	int user_ID; // user id
	string location; //device location
	string description; // item description
	string buyDate; //date when device bought
	float inventoryValue; //Inventory total value
	float setPrice; // device price
public:
	Device(string newName, int newDevice_ID, int newModel_ID, int newUser_ID, string newLocation, float newSetPrice, string newBuyDate, string newDescription) {
		name = newName;
		device_ID = newDevice_ID;
		model_ID = newModel_ID;
		user_ID = newUser_ID;
		location = newLocation;
		setPrice = newSetPrice;
		buyDate = newBuyDate;
		description = newDescription;
	}
	//used to return values/information/data
	string getName() { return name; }
	int getDevice_ID() { return device_ID; }
	int getModel_ID() { return model_ID; }
	int getUser_ID() { return user_ID; }
	string getLocation() { return location; }
	string getDescription() { return description; }
	float getPrice() { return setPrice; }
	string setDate() { return buyDate; }

};


class Inventory {
private:
	vector <Device> deviceList;
	int newid; // we will use this to get device id's.
public:
	Inventory();

	void removeDevice(); // remove Devices funtion

	void loadDevices(); //loads devices

	void saveDevices(); // saves devices

	void addDevice(); // add device

	void changeDevice(); // change devices information

	void showDevices(); // shows devices

	void showModelDevices(); //show devices, criterium - based by model

	void totalValue(); //displays inventory total value

	bool ConCmd_Menu(cmdArgs Args); // Command callbacks.
};