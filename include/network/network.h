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

#include <net/if.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <sys/socket.h>
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
std::string set_interface(){
    std::string out;
    struct ifaddrs *list, *ifa;
    if(getifaddrs(&list) == -1) return out;
    for(ifa = list; ifa; ifa = ifa->ifa_next){
        if(!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET) continue;
        if(!(ifa->ifa_flags & IFF_UP) || (ifa->ifa_flags & IFF_LOOPBACK)) continue;
        std::string n = ifa->ifa_name;
        if(access(("/sys/class/net/" + n + "/wireless").c_str(), F_OK) == 0){
            freeifaddrs(list);
            return n;
        }
        if(out.empty() && (n.rfind("eth",0) == 0 || n.rfind("en",0) ==0)) out = n;

    }
    freeifaddrs(list);
    return out;
}
#define interface set_interface()
#endif // interface

#ifndef network_ip
std::string get_ip(){
    struct ifaddrs *list, *ifa;
    std::string ip = "", eth_ip = "";
    if(getifaddrs(&list) == -1) return ip;

    for(ifa = list; ifa; ifa = ifa->ifa_next){
        if(!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET) continue;
        if(!(ifa->ifa_flags && IFF_UP) || (ifa->ifa_flags & IFF_LOOPBACK)) continue;

        std::string n = ifa->ifa_name;
        char buf[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr, buf, sizeof(buf));

        if(access(("/sys/class/net/" + n + "/wireless").c_str(), F_OK) == 0){
            ip = buf;
            break;
        }
        if(eth_ip.empty() && (n.rfind("eth",0) == 0 || n.rfind("en",0) == 0)){
            eth_ip = buf;
        }
    }
    freeifaddrs(list);
    return ip.empty() ? eth_ip : ip;
}
#define network_ip get_ip()
#endif // network_ip

#ifndef public_ip
std::string set_public_ip(){
    FILE* fp = popen("curl -s ifconfig.me", "r");
    char ip[64] = {0};
    fgets(ip, sizeof(ip), fp);
    pclose(fp);
    return std::string(ip);
}
#define public_ip set_public_ip()
#endif // public_ip

#endif // NETWORK_H