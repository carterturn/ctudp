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
#include "ctudp.h"

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

int ctudp::c_open(int port){
	if((socketid = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		cerr << "ctudp::c_open could not create socket\n";
		return socketid;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(socketid, (const sockaddr *) &addr, sizeof(addr)) < 0){
		cerr << "ctudp::c_open could not bind to port " << port << "\n";
		return 2;
	}
}

int ctudp::c_write(string data, string address, int port){
	if(data.length() > ctudp_max_packetsize){
		cerr << "ctudp::c_write: data size greater than " << ctudp_max_packetsize << " operation not supported\n";
		return -1;
	}
	sockaddr_in target;
	target.sin_family = AF_INET;
	target.sin_port = port;
	inet_aton(address.c_str(), &target.sin_addr);

	return sendto(socketid, data.c_str(), data.length(), 0, (sockaddr *) &target, sizeof(target));
}

string ctudp::c_read(std::string * address, int * port){
	unsigned char buffer[ctudp_max_packetsize];

	sockaddr_in source;
	unsigned int source_len;
	int length = recvfrom(socketid, buffer, ctudp_max_packetsize, 0, (sockaddr *) &source, &source_len);
	char * caddr = inet_ntoa(source.sin_addr);
	*address = caddr;
	*port = source.sin_port;

	string data = "";
	for(int i = 0; i < length; i++){
		data += buffer[i];
	}
	return data;
}

string ctudp::c_read(){
	unsigned char buffer[ctudp_max_packetsize];
	int length = recvfrom(socketid, buffer, ctudp_max_packetsize, 0, NULL, NULL);
	
	string data = "";
	for(int i = 0; i < length; i++){
		data += buffer[i];
	}
	return data;	
}

void ctudp::c_close(){
	close(socketid);
}
