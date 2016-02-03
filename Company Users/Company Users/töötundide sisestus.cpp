/*töötundide sisestus + tööülesanded
muutminekustutamine(admin ? )
enda tööde ülevaade,
kokkuvõte tundide arvust(kuu, nädal, aasta ? )

tundide arv, töötegija, töö kirjeldus,*/
#include "stdafx.h"
#include <string>
#include <vector>


struct Task
{
	static int newid;
	int task_id;
	int person_id;
	float hours;
	std::string description;

};
int Task::newid = 0;

class Workhour_System
{
private:
	std::vector<Task> list;
			
public:
	//Workhour_System();
	int add_task(int person_id , float hours , std::string description);
	void remove_task(int task_id);
	void daily_review(int task_id);
	void monthly_review(int task_id);

};

int Workhour_System::add_task(int person_id, float hours, std::string description)
{
	Task temptask;
	temptask.task_id = temptask.newid++;
	temptask.person_id = person_id;
	temptask.hours = hours;
	temptask.description = description;
	list.push_back(temptask);
	return temptask.task_id;

}
void Workhour_System::remove_task(int task_id)
{
	for (int i = 0; i < (int)list.size(); i++) {
		if (list[i].task_id = task_id) {
			list.erase(list.begin()+i);
			return;
		}
	}
}
void Workhour_System::daily_review(int task_id)
{

}
void Workhour_System::monthly_review(int task_id)
{

}