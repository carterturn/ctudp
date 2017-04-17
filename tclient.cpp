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
	
	socket.c_open(2324);

	socket.c_write("Hello how are you today. I am fine. Life is pretty good. Things are ok now.", "127.0.0.1", 2323);
	cout << socket.c_read() << "\n";

		socket.s_write("Hello how are you today. I am fine. Life is pretty good. Things are ok now.  int main(int argc, char* argv[]){ I am making this too too too too too too too too too too too too too too too too too too too too too too too too too too too too too too too too too too too too long", "127.0.0.1", 2323);
	cout << socket.s_read() << "\n";

	socket.c_close();
}
