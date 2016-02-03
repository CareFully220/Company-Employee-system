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

bool Device::ConCmd_addDevice(cmdArgs Args) 
{
	addDevice();
	return true;
}

Device::Device() {
	using namespace std::placeholders; // for `_1` placeholder

	ConsoleController::RegisterCommand("device_add", 0, PERM_MODIFYINVENTORY, std::bind(&Device::ConCmd_addDevice, this, _1), "Add a new device.");
	ConsoleController::RegisterCommand("device_change", 1, PERM_MODIFYINVENTORY, std::bind(&Device::ConCmd_addDevice, this, _1), "Params: <Device ID> | Change a device.");

	/*cout << "[3]Remove device" << endl; //removeDevice();
	cout << "[4]Inventory overview" << endl;  //showDevices();
	cout << "[5]Model-based overview" << endl; //showModelDevices();
	cout << "[6]Inventory total value" << endl; //totalValue();*/
}


void Device::addDevice() {
	fstream File("info.txt", fstream::in | fstream::out); //change later to devices.db file
	vector<Device*> deviceList;

	string record;
	while (getline(File, record)) {
		Device *newDevice = new Device();
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
		newDevice->setDevice(name, device_ID, model_ID, user_ID, location, setPrice, buyDate, description);
		deviceList.push_back(newDevice);
	}

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

	Device *newDevice = new Device();
	newDevice->setDevice(name, device_ID, model_ID, user_ID, location, setPrice, buyDate, description); // setPrice == buyPrice
	deviceList.push_back(newDevice);
	cout << "Device successfully added!" << endl;
	File.close();
	{
		ofstream File("info.txt");
		cout << deviceList.size();
		for (int i = 0; i < (int)deviceList.size(); i++) {
			File << deviceList[i]->getName() << ", ";
			File << deviceList[i]->getDevice_ID() << ", ";
			File << deviceList[i]->getModel_ID() << ", ";
			File << deviceList[i]->getUser_ID() << ", ";
			File << deviceList[i]->getLocation() << ", ";
			File << deviceList[i]->getDescription() << ", ";
			File << deviceList[i]->getPrice() << ", ";
			File << deviceList[i]->setDate() << "\n";
		}
		File.close();
	}
}

void Device::printMenu() {

	string input; // user option

	

												//cin >> input;
	getline(cin, input);

	if (input == "1") {
		addDevice();
	}
	else {
		cout << "lol" << endl;
	}
	/*
	switch (input) {
	case 1:
	addDevice();
	case 2:
	//changeDevice();
	case 3:
	//removeDevice();
	case 4:
	//DeviceList();
	case 5:
	//DeviceListByModel();
	case 6:
	//totalValue();
	default:
	cout << "Wrong input!" << endl;
	return;
	}
	*/
}

/*int main() {

	Device go;
	go.printMenu();

	system("pause");
}*/