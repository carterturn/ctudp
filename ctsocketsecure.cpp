/*
  Copyright 2016 Carter Turnbaugh

  This file is part of Terca C++ Sockets.

  Terca C++ Sockets is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Terca C++ Sockets is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Terca C++ Sockets.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ctsocketsecure.h"

using namespace std;

ctsocketsecure::ctsocketsecure(string key){
	register_cipher(&aes_desc);
	
	aes_key = key;
}

void ctsocketsecure::encryptstart(){
	cbc_start(find_cipher("aes"), (const unsigned char *) aes_key.c_str(), (const unsigned char *) aes_key.c_str(), 16, 0,&aes);
}

void ctsocketsecure::encryptend(){
	cbc_done(&aes);
}

string ctsocketsecure::decrypt(string data){
	unsigned char msg[data.length()];
	bzero(msg, data.length());
	
	cbc_decrypt((unsigned char *) data.c_str(), msg, data.length(), &aes);

	string result = string((const char*) msg).substr(0, data.length());
		
	return result.substr(0, result.find('\4'));
}

string ctsocketsecure::encrypt(string data){
	int padlength = ((data.length() / 16) + 1)*16 - data.length();
	for(int i = 0; i < padlength; i++) data += '\4';

	unsigned char emsg[data.length()];

	cbc_encrypt((const unsigned char *) data.c_str(), emsg, data.length(), &aes);

	string result = "";
	for(int i = 0; i < data.length(); i++){
		result += emsg[i];
	}

	return result;
}
