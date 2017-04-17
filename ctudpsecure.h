/*
  Copyright 2017 Carter Turnbaugh

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

#include "ctudp.h"
#include "ctsocketsecure.h"

class ctudpsecure : public ctudp, public ctsocketsecure {
public:
ctudpsecure(std::string key) : ctsocketsecure(key){}
	int s_write(std::string data, std::string address, int port){
		encryptstart();
		int result = c_write(encrypt(data), address, port);
		encryptend();
		return result;
	}
	std::string s_read(std::string * address, int * port){
		encryptstart();
		std::string result = decrypt(c_read(address, port));
		encryptend();
		return result;
	}
	std::string s_read(){
		encryptstart();
		std::string result = decrypt(c_read());
		encryptend();
		return result;
	}
};
