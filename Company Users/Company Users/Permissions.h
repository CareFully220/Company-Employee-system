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

/** @file Permissions.h
  * @brief List of all permission flags.
  */

#pragma once

#define PERM_USER ( 1 << 0 ) //!< If Employee has an account.
#define PERM_ALLOWLOGIN ( 1 << 1 ) //!< If Employee can login.
#define PERM_VIEWUSERS ( 1 << 2 )
#define PERM_VIEWINVENTORY ( 1 << 3 )
#define PERM_VIEWWORKHOURS ( 1 << 4 )
#define PERM_VIEWSALARY ( 1 << 5 )
#define PERM_MODIFYUSERS ( 1 << 6 )
#define PERM_MODIFYINVENTORY ( 1 << 7 )
#define PERM_MODIFYWORKHOURS ( 1 << 8 )
#define PERM_MODIFYSALARY ( 1 << 9 )
#define PERM_ADMIN ( 1 << 19 ) 
#define PERM_DELETED ( 1 << 20 ) //!< If Employee is deleted.

#define PERM_DEFAULT ( PERM_USER | PERM_ALLOWLOGIN | PERM_VIEWUSERS )
#define PERM_ROOT ( 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8 | 1 << 9 | 1 << 19 )