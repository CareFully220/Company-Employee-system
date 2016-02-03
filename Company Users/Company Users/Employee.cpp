#include "stdafx.h"
#include "Employee.h"

int Employee::newid = 0;

Employee::Employee(
	std::string firstname, std::string lastname,
	std::string SSID, std::string address,
	std::string gender, std::string position,
	std::string education, std::string nationality,
	std::string username, std::string password, std::string salt, int permissions) 
	: id(newid++)
{

	SetInfo(EINF_GENDER, gender);
	SetInfo(EINF_FIRSTNAME, firstname);
	SetInfo(EINF_LASTNAME, lastname);
	SetInfo(EINF_SSID, SSID);
	SetInfo(EINF_ADDRESS, address);
	SetInfo(EINF_POSITION, position);
	SetInfo(EINF_EDUCATION, education);
	SetInfo(EINF_NATIONALITY, nationality);

	this->username = username;
	this->password = password;
	this->salt = salt;
	this->permissions = permissions;

}


Employee::Employee(std::string firstname, std::string lastname) : id(newid++), permissions(PERM_USER) {
	SetInfo(EINF_FIRSTNAME, firstname);
	SetInfo(EINF_LASTNAME, lastname);
}

// Creates account for user
void Employee::CreateAccount(std::string username, std::string password, int perms)
{
	this->username = username;
	SetPassword(password);
	this->permissions = perms;
}

// Adds user permissions
void Employee::AddPermission(int perm)
{
	permissions |= perm;
}

// Removes user permissions
void Employee::RemovePermission(int perm)
{
	permissions |= ~perm;
}

// Get user permissions.
int Employee::GetPermissions()
{
	return permissions;
}

// Check if user has specific permission.
bool Employee::GetPermission(int perm)
{
	if (permissions & perm)
		return true;
	else
		return false;
}


// Get Functions
int Employee::GetID()	
{
	return id;
}
std::string Employee::GetInfo(EInfo infoID)
{
	if (infoID <= 0 && infoID < EINFOS) {
		return Info[infoID];
	}
	else {
		return "";
	}
	
}
bool Employee::SetInfo(EInfo infoID, std::string value)
{
	if (infoID <= 0 && infoID < EINFOS) {
		Info[infoID] = value;
		return true;
	}
	else return false;
}
std::string Employee::GetUsername()
{
	return username;
}
std::string Employee::GetPassword()
{
	return password;
}
std::string Employee::GetSalt()
{
	return salt;
}
// Sets password for the user
void Employee::SetPassword(std::string Passwd)
{
	salt = CreateSalt();
	password = sha256(Passwd, salt);
	
}

// Checks password for the user
bool Employee::CheckPassword(std::string Passwd)
{
	std::string hash;
	hash = sha256(Passwd, salt);
	if (password.compare(hash) == 0) {
		return true;
	}
	return false;
}

std::string Employee::CreateSalt()
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	std::string s;
	for (int i = 0; i < 10; ++i) {
		s += alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	return s;
}