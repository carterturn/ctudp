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

#include <iostream>
#include "ctudpsecure.h"

using namespace std;

int main(int argc, char* argv[]){
	ctudpsecure socket = ctudpsecure("qwerasdfqwerasdf");

	cout << socket.c_open(2323) << "\n";

	string remote;
	int remote_port;
	cout << socket.c_read(&remote, &remote_port) << "\n";
	cout << remote << ":" << remote_port << "\n";
	socket.c_write("Hello how are you today", "127.0.0.1", 2324);

	cout << socket.s_read(&remote, &remote_port) << "\n";
	cout << remote << ":" << remote_port << "\n";
	socket.s_write("More about you, hello how are you today   Terca C++ UDP is free software: you can redistribute it and/or modify it under the terms of the GNU GPL.", "127.0.0.1", 2324);

	socket.c_close();
}
