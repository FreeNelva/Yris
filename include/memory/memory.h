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

#ifndef MEMORY_H
#define MEMORY_H

#include <cstdio>
#include <string>
#include <sys/sysinfo.h>

#ifndef mem_size
double m_size(){
    struct sysinfo info;
    if(sysinfo(&info) != 0){
        return -1;
    }
    return static_cast<double>(info.totalram) * info.mem_unit / ( 1024.0 * 1024.0 * 1024.0);
}
#define mem_size m_size()
#endif // mem_size

#ifndef mem_type
std::string get_type(){
    std::string t;
    if(FILE* p = popen("dmidecode -t 17 | awk '/Type:/&&!/Error/{print $2;exit}'", "r")){
        char b[32] = {0};
        if(fgets(b, 32, p)) t = b;
        pclose(p);
    }
    if(t.length() < 4) return "Unknown";
    switch (t[3]){
        case '3':
            return "DDR3";
        case '4':
            return "DDR4";
        case '5':
            return "DDR5";
        default:
            return "Other";
    }
}
#define mem_type get_type()
#endif // mem_type

#endif // MEMORY_H