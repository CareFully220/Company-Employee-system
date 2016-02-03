#pragma once
/**
* @file Employee.h
* @brief Everyting nessescary for the employee(s) account including few functions.
* 
* 
*
*/


#include <fstream>
#include <vector>
#include <string>
#include "Permissions.h"
#include "sha256.h"

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

const std::string EmployeeInfoNames[EINFOS] = {
	"firstname",
	"lastname",
	"ssid",
	"address",
	"gender",
	"position",
	"education",
	"nation",
	"department"
};

/**
  * This class is responsible for all the information what one employee account should include.
  */
class Employee {
	static int newid;
	const int id;
	int gender;

	std::string Info[EINFOS];

	std::string username;
	std::string password;
	std::string salt;
	int permissions;

	// Private functions come here:
	std::string CreateSalt(); //!< Creates a 10 character random string.

	//! Used to create empty employee object.
	Employee() : id(newid++), permissions(PERM_USER) {
	}

public:
	//! Should only be used when loading employees from file. This Constructor needs already hashed password.
	Employee(
		std::string firstname, std::string lastname,
		std::string SSID, std::string address, 
		std::string gender, std::string position, 
		std::string education, std::string nationality,
		std::string username, std::string password, std::string salt, int permissions);

	
	//! Used to create standard new employee object.
	Employee(std::string firstname, std::string lastname);
	
	//! Create an account ( username, password and permissions )
	void CreateAccount(std::string username, std::string password, int perms = PERM_USER | PERM_ALLOWLOGIN);

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

};