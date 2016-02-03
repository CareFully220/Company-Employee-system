#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "ConsoleController.h"
#include "Permissions.h"
using namespace std;

//class about device
class Device {
protected:
	string name; // device name
	string getName() {
		return name;
	}
	string device_ID; // device id
	string getDevice_ID() {
		return device_ID;
	}
	string model_ID; // device model id
	string getModel_ID() {
		return model_ID;
	}
	string user_ID; // user id
	string getUser_ID() {
		return user_ID;
	}
	string location; //device location
	string getLocation() {
		return location;
	}
	string description; // item description
	string getDescription() {
		return description;
	}
	//float buyPrice;  //Device price
	string setPrice; //setting device price // it was  float buyPrice;
	string getPrice() {
		return setPrice;
	}
	string buyDate; //date when device bought
	string setDate() {
		return buyDate;
	}
	double inValue; //Inventory total value

	bool ConCmd_addDevice(cmdArgs Args);


public:
	Device();


	void setDevice(string newName, string newDevice_ID, string newModel_ID, string newUser_ID, string newLocation, string newSetPrice, string newBuyDate, string newDescription) {
		name = newName;
		device_ID = newDevice_ID;
		model_ID = newModel_ID;
		user_ID = newUser_ID;
		location = newLocation;
		setPrice = newSetPrice;
		buyDate = newBuyDate;
		description = newDescription;
	}
	void addDevice(); // add device
					  //void changeDevice(); // change stuff
					  //void removeDevice(); // remove item
					  //void DeviceList(); // shows all devices
					  //void DeviceListByModel(); //show devices, criterium - based by model
					  //void totalValue(); //displays inventory total value
	void printMenu(); //prints functions
};