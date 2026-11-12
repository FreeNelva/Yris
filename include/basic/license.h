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

#ifndef YRIS_LICENSE_HPP
#define YRIS_LICENSE_HPP
#endif // YRIS_LICENSE_HPP

#include <string>
#include <iostream>

std::string license_text = R"(
Yris  Copyright (C) 2026  cynthefer@gmail.com<Ntando Khanyile>
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.
)";

void show_license() {
    std::cout << license_text << std::endl;
};