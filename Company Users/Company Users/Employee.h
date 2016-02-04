/* *********************************************************************
* Employee User System
* Copyright 2016 Marvin Hestein, Lauri Mäe
*
* This file is part of Employee User System.
*
* Employee User System is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Employee User System 2k16 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Employee User System. If not, see <http://www.gnu.org/licenses/>.
*
* ********************************************************************/

/**
* @file Employee.h
* @brief Everyting nessescary for the employees.
*
*/
#pragma once

#include <fstream>
#include <vector>
#include <string>
#include "Permissions.h"
#include "sha256.h"

//! Informations that can be saved for each employee.
enum EInfo {
	EINF_INVALID = -1,
	EINF_FIRSTNAME,
	EINF_LASTNAME,
	EINF_SSID,
	EINF_ADDRESS,
	EINF_GENDER,
	EINF_POSITION,
	EINF_EDUCATION,
	EINF_NATIONALITY,
	EINF_DEPARTMENT,

	EINFOS
};
//! The names of the Informations.
const std::string EmployeeInfoNames[EINFOS] = {
	"firstname",
	"lastname",
	"ssid",
	"address",
	"gender",
	"position",
	"education",
	"nationality",
	"department"
};

/**
  * Responsible for all the information what one employee account should have.
  */
class Employee {
	static int newid;
	int id;

	std::string Info[EINFOS];

	std::string username;
	std::string password;
	std::string salt;
	int permissions;

	// Private functions come here:
	std::string CreateSalt(); //!< Creates a 10 character random string.

	//! Used to create empty employee object.
	Employee() : id(newid++), permissions(0) {
	}

public:

	//! Should only be used when loading employees from file. This Constructor needs already hashed password.
	Employee(
		int id,
		std::string firstname, std::string lastname,
		std::string SSID, std::string address, 
		std::string gender, std::string position, 
		std::string education, std::string nationality,
		std::string username, std::string password, std::string salt, int permissions);

	
	//! Used to create standard new employee object.
	Employee(std::string firstname, std::string lastname);
	
	//! Create an account ( username, password and permissions )
	void CreateAccount(std::string username, std::string password, int perms = PERM_DEFAULT);

	void AddPermission(int perm); //!< Add permissions

	void RemovePermission(int perm); //!< Remove permissions

	/** Check if given password matches with the Employees password.
	  *
	  * @param Passwd Password to check
	  * @returns True if passwords match. False otherwise.
	  *
	  */
	bool CheckPassword(std::string Passwd);

	int GetPermissions();	//!< Get user permissions.
	std::string GetUsername();	//!< Returns the username of employees account
	std::string GetPassword();	//!< Returns the password of employees account
	std::string GetSalt();		//!< Returns the salt used to hash the password.


	//! Check if user has a specific permission.
	//! @param perm pecific permission.
	//! @see Permissions.h
	bool GetPermission(int perm);

	bool IsRemoved();

	int GetID();				//!< Returns employees ID

	/** Get employee's info	
	  * @param infoID Infoid that you want. 
	  * @see EInfo
	  * @returns Info value or '\0' if Info with specified InfoID was not found. 
	  */
	std::string GetInfo(EInfo infoID);	

	/** Set employee's info
	  *
	  * @param infoID Infoid that you want to set.
	  * @param value New value of that info.
	  * @see EInfo
	  * @returns True if successful. False if Info with specified InfoID was not found. 
	  */
	bool SetInfo(EInfo infoID, std::string value);

	//! Set new password.
	void SetPassword(std::string Passwd);

	// assignment operator
	/*Employee& Employee::operator= (const Employee &cSource)
	{
		// check for self-assignment by comparing the address of the
		// implicit object and the parameter
		if (this == &cSource)
			return *this;

		// do the copy
		newid = cSource.newid;
		id = cSource.id;
		gender = cSource.gender;

		for (int i = 0; i < EINFOS; i++) {
			Info[i] = cSource.Info[i];
		}
		username = cSource.username;
		password = cSource.password;
		salt = cSource.salt;
		permissions = cSource.permissions;

		// return the existing object
		return *this;
	}*/

};