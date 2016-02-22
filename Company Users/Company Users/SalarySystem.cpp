#include "stdafx.h"
#include "SalarySystem.h"
//#include "Workhoursystem.h"
using namespace std;

//constructor
SalarySystem::SalarySystem(EmployeeList *EmpList)
{
	this->EmpList = EmpList;
	using namespace std::placeholders;

	ConsoleController::RegisterCommand("addemployeeexpense", 0, PERM_MODIFYSALARY,
		bind(&SalarySystem::ConCmd_AddEmployeeExpense, this, _1),
		"Adds employee expense.");

	loadFile();
}

//get functions
string SalarySystem::getID()
{
	return sID;
}
string SalarySystem::getWorkHours()
{
	return sWorkHours;
}
string SalarySystem::getJobPayRate()
{
	return sJobPayRate;
}
string SalarySystem::getSalary()
{
	return sSalary;
}
string SalarySystem::getFica()
{
	return sFica;
}
string SalarySystem::getUip()
{
	return sUip;
}
string SalarySystem::getSalaryExpense()
{
	return sSalaryExpense;
}
string SalarySystem::getBonus()
{
	return sBonus;
}
string SalarySystem::getBonusFica()
{
	return sBonusFica;
}
string SalarySystem::getBonusUip()
{
	return sBonusUip;
}
string SalarySystem::getBonusExpense()
{
	return sBonusExpense;
}
string SalarySystem::getTotalExpense()
{
	return sTotalExpense;
}

//calculation functions
float SalarySystem::calSalary(float workHours, float jobPayRate)
{
	return workHours * jobPayRate;
}
float SalarySystem::calFica(float salary)
{
	return ficaRate * salary;
}
float SalarySystem::calUip(float salary)
{
	return uipRate * salary;
}
float SalarySystem::calSalaryExpense(float salary, float fica, float uip)
{
	return salary + fica + uip;
}
float SalarySystem::calBonusFica(float bonus)
{
	return ficaRate * bonus;
}
float SalarySystem::calBonusUip(float bonus)
{
	return uipRate * bonus;
}
float SalarySystem::calExpense(float salary, float fica, float uip)
{
	return salary + fica + uip;
}
float SalarySystem::calBonusExpense(float bonus, float bonusFica, float bonusUip)
{
	return bonus + bonusFica + bonusUip;
}
float SalarySystem::calTotalExpense(float salaryExpense, float bonusExpense)
{
	return salaryExpense + bonusExpense;
}

//EmployeeExpense.db functions
void SalarySystem::loadFile()
{
	ifstream file("EmployeeExpense.db");
	string record;

	while (getline(file, record))
	{
		istringstream ss(record);
		string field, ID, workHours, jobPayRate, salary, fica, uip,
			salaryExpense, bonus, bonusFica, bonusUip, bonusExpense, totalExpense;

		getline(ss, field, ','); ID = field;
		getline(ss, field, ','); workHours = field;
		getline(ss, field, ','); jobPayRate = field;
		getline(ss, field, ','); salary = field;
		getline(ss, field, ','); fica = field;
		getline(ss, field, ','); uip = field;
		getline(ss, field, ','); salaryExpense = field;
		getline(ss, field, ','); bonus = field;
		getline(ss, field, ','); bonusFica = field;
		getline(ss, field, ','); bonusUip = field;
		getline(ss, field, ','); bonusExpense = field;
		getline(ss, field, ','); totalExpense = field;

		int	iID = atoi(ID.c_str());
		int	iWorkHours = atoi(workHours.c_str());
		float fJobPayRate = atof(jobPayRate.c_str());
		float fSalary = atof(salary.c_str());
		float fFica = atof(fica.c_str());
		float fUip = atof(uip.c_str());
		float fSalaryExpense = atof(salaryExpense.c_str());
		float fBonus = atof(bonus.c_str());
		float fBonusFica = atof(bonusFica.c_str());
		float fBonusUip = atof(bonusUip.c_str());
		float fBonusExpense = atof(bonusExpense.c_str());
		float fTotalExpense = atof(totalExpense.c_str());

		salaryList.push_back(SalarySystem(iID, iWorkHours, fJobPayRate, fSalary, fFica,
			fUip, fSalaryExpense, fBonus, fBonusFica, fBonusUip, fBonusExpense, fTotalExpense));
	}
	file.close();
}

void SalarySystem::saveFile()
{
	ofstream file("EmployeeExpense.db");

	for (int i = 0; i < (int)salaryList.size(); i++)
	{
		file << salaryList[i].getID() << ", ";
		file << salaryList[i].getWorkHours() << ", ";
		file << salaryList[i].getJobPayRate() << ", ";
		file << salaryList[i].getSalary() << ", ";
		file << salaryList[i].getFica() << ", ";
		file << salaryList[i].getUip() << ", ";
		file << salaryList[i].getSalaryExpense() << ", ";
		file << salaryList[i].getBonus() << ", ";
		file << salaryList[i].getBonusFica() << ", ";
		file << salaryList[i].getBonusUip() << ", ";
		file << salaryList[i].getBonusExpense() << ", ";
		file << salaryList[i].getTotalExpense() << ", " << endl;
	}
	file.close();
}

void SalarySystem::addExpense()
{
	string choice, input, uID, uWorkHours, uSalary, uFica, uUip,
		uSalaryExpense, uBonus, uBonusFica, uBonusUip, uBonusExpense, uTotalExpense;
	float fJobPayRate;

	while (true)
	{
		cout << "Enter employee ID: ";
		getline(cin, uID);
		int iID = atoi(uID.c_str());

		if (!EmpList->IsValidID(iID)) {
			cout << "There is no employee with ID: " << iID << endl;
			break;
		}



		//temporary (will come from workhour system)
		cout << "Enter worked hours: ";
		getline(cin, uWorkHours);



		//jobPayRate
		string Pos = EmpList->GetEmployeeInfo(iID, EINF_POSITION);
		if (Pos == "ylemus") {
			fJobPayRate = 10;
		}
		else if (Pos == "programmeerija") {
			fJobPayRate = 8;
		}
		else if (Pos == "koristaja") {
			fJobPayRate = 5;
		}
		else {
			cout << "Please set position for employee with ID " << uID << " before continueing!" << endl;
			break;
		}
		
		int iWorkHours = atoi(uWorkHours.c_str());
		float fSalary = calSalary((float)iWorkHours, fJobPayRate);
		float fFica = calFica(fSalary);
		float fUip = calUip(fSalary);
		float fSalaryExpense = calSalaryExpense(fSalary, fFica, fUip);

		cout << "Add bonus?" << endl;
		cout << "[1]Yes" << endl;
		cout << "[2]No" << endl;
		getline(cin, choice);
		if (choice == "1")
		{
			cout << "Enter amount: " << endl;
			getline(cin, input);
			uBonus = input;
		}
		else
		{
			uBonus = "0";
		}

		float fBonus = atof(uBonus.c_str());
		float fBonusFica = calBonusFica(fBonus);
		float fBonusUip = calBonusUip(fBonus);
		float fBonusExpense = calBonusExpense(fBonus, fBonusFica, fBonusUip);

		float fTotalExpense = calTotalExpense(fSalaryExpense, fBonusExpense);

		salaryList.push_back(SalarySystem(iID, iWorkHours, fJobPayRate, fSalary, fFica,
			fUip, fSalaryExpense, fBonus, fBonusFica, fBonusUip, fBonusExpense, fTotalExpense));

		cout << "Expense added succesfully" << endl;
		saveFile();
		break;
	}
}

//add employee expense to EmployeeExpense.db
bool SalarySystem::ConCmd_AddEmployeeExpense(cmdArgs Args)
{
	string input;

	while (true)
	{
		cout << "============================" << endl;
		cout << "[1]Add expense" << endl;
		cout << "[2]Exit" << endl;

		getline(cin, input);

		if (input == "1")
		{
			addExpense();
		}
		else if (input == "2")
		{
			break;
		}
		else
		{
			cout << "Invalid input!" << endl;
			continue;
		}
	}
	return true;
}