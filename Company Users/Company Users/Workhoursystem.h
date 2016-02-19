#pragma once

#include "ConsoleController.h"
#include <vector>

struct Task
{
	int newid = 0;
	int task_id;
	int person_id;
	float hours;
	int month;
	std::string description;

};


class WorkhourSystem
{
private:
	std::vector<Task> list;

public:
	WorkhourSystem();
	bool ConCmd_mmain(cmdArgs Args);
	int add_task(int person_id, float hours, int month, std::string description);
	void remove_task(int task_id);
	void review(int task_id);
	void readFile();
	void saveFile();
	int search(int person_id);
	int search_month(int person_id, int month);

};
WorkhourSystem::WorkhourSystem() {
	ConsoleController::RegisterCommand("workhoursystem",
		0,
		PERM_VIEWWORKHOURS,
		std::bind(&WorkhourSystem::ConCmd_mmain, this, _1), 
		"Work hour system");
	
}
void WorkhourSystem::readFile()
{
	ifstream ifile;
	ifile.open("in_t66tunnid.db");
	string rida;
	while (getline(ifile, rida))
	{
		Task temp;
		stringstream(rida);
		string lahter;
		rida >> lahter;
		temp.person_id = atoi(lahter.c_str());
		rida >> lahter;
		temp.hours = atoi(lahter.c_str());
		rida >> lahter;
		temp.description = lahter;
		list.push_back(temp);

	}

	ifile.close();
}
void WorkhourSystem::saveFile()
{

	ofstream ofile;
	ofile.open("out_t66tunnid.db");
	for (auto &it : list) {
		ofile << it.month << " " << it.person_id << " " << it.hours << " " << it.description << endl;
	}
	ofile.close();
}

int WorkhourSystem::add_task(int person_id, float hours, int month, std::string description)
{
	Task temptask;
	temptask.task_id = temptask.newid++;
	temptask.month = month;
	temptask.person_id = person_id;
	temptask.hours = hours;
	temptask.description = description;
	list.push_back(temptask);
	return temptask.task_id;

}
void WorkhourSystem::remove_task(int task_id)
{
	for (int i = 0; i < (int)list.size(); i++) {
		if (list[i].task_id = task_id) {
			list.erase(list.begin() + i);
			return;
		}
	}
}
void WorkhourSystem::review(int task_id)
{
	cout << "Month\t" << "Person_id\t" << "Workhours\t" << "Description\t" << "\n";
	for (int i = 0; i < list.size(); i++) {
		cout << list[i].month << "\t" << list[i].person_id << "\t\t" << list[i].hours << "\t\t" << list[i].description << "\n";

	}
}
int WorkhourSystem::search(int person_id)
{
	int size = 0;

	for (int i = 0; i < list.size(); i++) {
		if (list[i].person_id == person_id) {
			size += list[i].hours;

		}

	}
	return size;
}
int WorkhourSystem::search_month(int person_id, int month)
{
	int size = 0;

	for (int i = 0; i < list.size(); i++) {
		if (list[i].person_id == person_id && list[i].month == month) {
			size += list[i].hours;

		}

	}
	return size;
}
bool WorkhourSystem::ConCmd_mmain(cmdArgs Args) {
	WorkhourSystem mySystem = WorkhourSystem();
	mySystem.add_task(1, 8, 1, "lal");
	mySystem.add_task(2, 8, 2, "lel");
	mySystem.add_task(3, 15, 1, "lel");
	mySystem.add_task(2, 9, 1, "lel");
	mySystem.add_task(2, 20, 2, "lel");
	mySystem.saveFile();
	mySystem.review(0);
	int id;
	cout << "type person_id:   ";
	cin >> id;
	cout << "type month:   ";
	int month;
	cin >> month;
	cout << mySystem.search_month(id, month);
	cin >> id;
	return 0;
}
