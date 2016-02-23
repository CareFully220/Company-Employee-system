#pragma once

#include "ConsoleController.h"
#include <vector>

using namespace std;


// Note by Care:
	// Changed hours to integer, since you tried to always add int to that.
	// Obviously it produced warnings. And you never used it as a float.
	// You can now delete this message.

struct WorkTask
{
	int newid = 0;
	int task_id;
	int person_id;
	int hours;
	int month;
	std::string description;

};


class WorkhourSystem
{
private:
	vector<WorkTask> list;

public:
	WorkhourSystem();
	bool ConCmd_mmain(cmdArgs Args);
	int add_task(int person_id, int hours, int month, std::string description);
	void remove_task(int task_id);
	void review(int task_id);
	void readFile();
	void saveFile();
	int search(int person_id);
	int search_month(int person_id, int month);

};
WorkhourSystem::WorkhourSystem() {
	using namespace placeholders; // for `_1` placeholder

	ConsoleController::RegisterCommand("workhoursystem",
		0,
		PERM_VIEWWORKHOURS,
		bind(&WorkhourSystem::ConCmd_mmain, this, _1), 
		"Work hour system");
	
}
void WorkhourSystem::readFile()
{
	ifstream ifile;
	ifile.open("t66tunnid.db");
	string rida;
	while (getline(ifile, rida))
	{
		WorkTask temp;
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
	ofile.open("t66tunnid.db");
	for (int i = 0; i < (int)list.size(); i++) {
		ofile << list[i].month << " " << list[i].person_id << " " << list[i].hours << " " << list[i].description << endl;
	}
	ofile.close();
}

int WorkhourSystem::add_task(int person_id, int hours, int month, std::string description)
{
	WorkTask temptask;
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
	for (int i = 0; i < (int)list.size(); i++) {
		cout << list[i].month << "\t" << list[i].person_id << "\t\t" << list[i].hours << "\t\t" << list[i].description << "\n";

	}
}
int WorkhourSystem::search(int person_id)
{
	int size = 0;

	for (int i = 0; i < (int)list.size(); i++) {
		if (list[i].person_id == person_id) {
			size += list[i].hours;

		}

	}
	return size;
}
int WorkhourSystem::search_month(int person_id, int month)
{
	int size = 0;

	for (int i = 0; i < (int)list.size(); i++) {
		if (list[i].person_id == person_id && list[i].month == month) {
			size += list[i].hours;

		}

	}
	return size;
}
bool WorkhourSystem::ConCmd_mmain(cmdArgs Args) {
	add_task(1, 8, 1, "lal");
	add_task(2, 8, 2, "lel");
	add_task(3, 15, 1, "lel");
	add_task(2, 9, 1, "lel");
	add_task(2, 20, 2, "lel");
	saveFile();
	review(0);
	cout << "type person_id: ";
	int id = ConsoleController::cinnum();
	cout << "type month: ";
	int month = ConsoleController::cinnum();
	cout << search_month(id, month);
	return 0;
}
