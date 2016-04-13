/*
  Copyright 2016 Carter Turnbaugh

  This file is part of Terca C++ UDP.

  Terca C++ UDP is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Terca C++ UDP is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Terca C++ UDP.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <iostream>

const size_t ctudp_max_packetsize = 256;

class ctudp {

public:
	int c_open(int port);
	int c_write(std::string data, std::string address, int port);
	std::string c_read();
	std::string c_read(std::string * address, int * port);
	void c_close();
protected:
	int socketid;
};
