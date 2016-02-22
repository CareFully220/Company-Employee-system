//INVENTORY SYSTEM H//
/*=========================================================================//
Made by: Karl Robert Lillipuu & Kevin Jasson(a little bit)
People who helped(many thanks!): Lauri Mäe, Marvin Helstein, Samael Tamm
//=========================================================================*/
/*===================================================================================================================//
 INTRODUCTIONS - here is comments what's in this header file
			   - Device information declarations are in the class called: Device
					* string name - device name
					* int device_ID - device unique id
					* int user_ID - device user
					* string location - where the device is used
					* string description - describes device / extra information about device
					* float price - device price
					* string date - device date(when bought)
					* float inventoryValue - displays inventory whole value
			   - All the functions(also deviceList vector) are declared in class called: Inventory
//=====================================================================================================================*/
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "ConsoleController.h"
using namespace std;

//class about device
class Device {
protected:
	string name; // device name
	int device_ID; // device id
	int model_ID; // device model id
	int user_ID; // user id
	string location; //device location
	string description; // item description
	float Price; // device price
	string Date; //date when device bought
	float inventoryValue; //Inventory total value
public:

	Device(string newName, int newDevice_ID, int newModel_ID, int newUser_ID, string newLocation, float newSetPrice, string newBuyDate, string newDescription) {
		name = newName;
		device_ID = newDevice_ID;
		model_ID = newModel_ID;
		user_ID = newUser_ID;
		location = newLocation;
		Price = newSetPrice;
		Date = newBuyDate;
		description = newDescription;
	}
	//used to return values/information/data
	string getName() { return name; }
	int getDevice_ID() { return device_ID; }
	int getModel_ID() { return model_ID; }
	int getUser_ID() { return user_ID; }
	string getLocation() { return location; }
	string getDescription() { return description; }
	float getPrice() { return Price; }
	string getDate() { return Date; }


	//these are used to change/modify device information
	void setName() { cout << "Enter new name for device: ";  string input;  getline(cin, input); name = input; }
	void setDevice_ID() { cout << "Enter new device ID : ";  int input;  input = ConsoleController::cinnum(); device_ID = input; }
	void setModel_ID() { cout << "Enter new model ID: ";  int input;  input = ConsoleController::cinnum(); model_ID = input; }
	void setUser_ID() { cout << "Enter new user ID: "; int input;  input = ConsoleController::cinnum(); user_ID = input; }
	void setLocation() { cout << "Enter new location: "; string input;  getline(cin, input); location = input; }
	void setDescription() { cout << "Enter new description: "; string input;  getline(cin, input); description = input; }
	void setPrice() { cout << "Enter new price: "; float input;  cin >> input; Price = input; }
	void setDate() { cout << "Enter new date for the device (DD.MM.YY): ";  string input;  getline(cin, input); Date = input; }
};


class Inventory {
private:
	EmployeeList* EmpList;
	vector <Device> deviceList;
	int newid; // we will use this to get device id's.
public:
	Inventory(EmployeeList* newEmpList);

	void removeDevice(); // remove Devices funtion

	void loadDevices(); //loads devices

	void saveDevices(); // saves devices

	void addDevice(); // add device

	void changeDevice(); // change devices information

	void showDevices(); // shows devices

	void showModelDevices(); //show devices, criterium - based by model

	void totalValue(); //displays inventory total value

	void deviceInfo(); //displays specific device all information(name,device_Id etc)

	void saveChanges(); // used for save changes

	bool ConCmd_Menu(cmdArgs Args); // Command callbacks.
};