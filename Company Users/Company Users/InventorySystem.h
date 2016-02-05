/*==========================================================================
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
==========================================================================*/

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
	string device_ID; // device id
	string model_ID; // device model id
	string user_ID; // user id
	string location; //device location
	string description; // item description
	//float buyPrice;  //Device price
	string setPrice; //setting device price // it was  float buyPrice;
	//float buyPrice = stof(setPrice);
	string buyDate; //date when device bought
	double inValue; //Inventory total value
public:

	Device(string newName, string newDevice_ID, string newModel_ID, string newUser_ID, string newLocation, string newSetPrice, string newBuyDate, string newDescription) {
		name = newName;
		device_ID = newDevice_ID;
		model_ID = newModel_ID;
		user_ID = newUser_ID;
		location = newLocation;
		setPrice = newSetPrice;
		buyDate = newBuyDate;
		description = newDescription;
	}
	string getName() { return name; }
	string getDevice_ID() { return device_ID; }
	string getModel_ID() { return model_ID; }
	string getUser_ID() { return user_ID; }
	string getLocation() { return location; }
	string getDescription() { return description; }
	string getPrice() { return setPrice; }
	string setDate() { return buyDate; }

};


class Inventory {
private:
	vector <Device> deviceList;
	int newid; // we will use this to get device id's.
public:

	Inventory();

	//void addDevice(string newName, string newDevice_ID, string newModel_ID, string newUser_ID, string newLocation, string newSetPrice, string newBuyDate, string newDescription);
	bool removeDevice(string Device_ID);

	void loadDevices();
	void saveDevices();

	void addDevice(); // add device
					  //void changeDevice(); // change stuff
					  //void removeDevice(); // remove item
					  //void DeviceList(); // shows all devices
					  //void DeviceListByModel(); //show devices, criterium - based by model
					  //void totalValue(); //displays inventory total value

					  // Command callbacks.
	bool ConCmd_Menu(cmdArgs Args);

};