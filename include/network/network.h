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

#ifndef NETWORK_H
#define NETWORK_H

#include <cstdio>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/utsname.h>

struct utsname network_info;
void set_network_info() {
    if (uname(&network_info) == -1) {
        //
    }
}

#ifndef hostname
#define hostname network_info.nodename
#endif

#ifndef domainname
#define domainname network_info.domainname
#endif

#ifndef interface
#ifndef local_ip
void set_interface(){
    struct ifaddrs* ifaddr = nullptr;
    if (getifaddrs(&ifaddr) == -1) {
        // Handle error
        return;
    }

    for (struct ifaddrs* ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr) {
            continue;
        }

        int family = ifa->ifa_addr->sa_family;
        if (family == AF_INET || family == AF_INET6) {
            char ip[INET6_ADDRSTRLEN];
            void* addr_ptr = (family == AF_INET) ? (void*)&((struct sockaddr_in*)ifa->ifa_addr)->sin_addr : (void*)&((struct sockaddr_in6*)ifa->ifa_addr)->sin6_addr;
            inet_ntop(family, addr_ptr, ip, sizeof(ip));
            #define interface ifa->ifa_name
            #define local_ip ip
        }
    }
    freeifaddrs(ifaddr);
}
#endif // local_ip
#endif // interface

#ifndef public_ip
void set_public_ip(){
    FILE* fp = popen("curl -s ifconfig.me", "r");
    char ip[64] = {0};
    fgets(ip, sizeof(ip), fp);
    #define public_ip ip
    pclose(fp);
}
#endif // public_ip

#endif // NETWORK_H