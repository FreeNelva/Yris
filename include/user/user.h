/*
Yris ; a unix tool  print simple specifications.
Copyright (C) 2026  cynthefer@gmail.com<Ntando Khanyile>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef USER_H
#define USER_H

#include <pwd.h>
#include <unistd.h>

uid_t userid = getuid(); // Get the user ID of the current user
struct passwd *pw = getpwuid(userid); // Get the passwd struct for the current user

#ifndef username
#define username pw->pw_name // Get the username from the passwd struct
#endif

#ifndef fullname
#define fullname pw->pw_gecos // Get the full name from the passwd struct
#endif

#ifndef userid
#define userid pw->pw_uid // Get the user ID from the passwd struct
#endif

#ifndef groupid
#define groupid pw->pw_gid // Get the group ID from the passwd struct
#endif

#endif // USER_H