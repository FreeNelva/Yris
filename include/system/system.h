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

#ifndef SYSTEM_H
#define SYSTEM_H

#include <pwd.h>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sys/utsname.h>

struct utsname system_info;
void set_uname() {
    if (uname(&system_info) == -1) {
        perror("uname");
        exit(EXIT_FAILURE);
    }
}   

#ifndef kernel
#define kernel system_info.sysname
#endif

#ifndef version
#define version system_info.release
#endif

#ifndef architecture
#define architecture system_info.machine
#endif

#ifndef release
#define release system_info.version
#endif

uid_t user_sys = getuid(); // Get the user ID of the current user
struct passwd *pw_sys = getpwuid(user_sys); // Get the passwd struct for the current user

#ifndef shell
#define shell pw_sys->pw_shell // Get the shell of the current user
#endif

#ifndef distribution
std::ifstream os_release_file("/etc/os-release");
std::string line;
void set_distribution(){
    while (std::getline(os_release_file, line)) {
        if (line.find("PRETTY_NAME=") == 0) {
            std::string distribution_name = line.substr(13, line.length() - 14);
            #define distribution distribution_name.c_str()
            break;
        }
    }
}
#endif


#endif // SYSTEM_H