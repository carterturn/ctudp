/*
  Copyright 2017 Carter Turnbaugh

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

#include <cstring> // bzero

using namespace std;

ctsocketsecure::ctsocketsecure(string key_string){
	key.data = (unsigned char *) key_string.c_str();
	key.size = key_string.length();
	gnutls_datum_t iv;
	iv.data = (unsigned char *) "unused_tmp_iv!!!";
	iv.size = 16;

	gnutls_cipher_init(&cipher_handle, GNUTLS_CIPHER_AES_256_CBC, &key, &iv);
}

string ctsocketsecure::decrypt(string data){
	char iv[16];
	memcpy(iv, data.c_str(), 16);
	data.erase(0, 16);
	
	unsigned char plaintext[data.length()];
	bzero(plaintext, data.length());

	gnutls_cipher_set_iv(cipher_handle, iv, 16);

	gnutls_cipher_decrypt2(cipher_handle, data.c_str(), data.length(), plaintext, data.length());

	string result = "";
	for(int i = 0; i < data.length(); i++){
		result += plaintext[i];
	}
	
	return result.substr(0, result.find('\4'));
}

string ctsocketsecure::encrypt(string data){
	int pad_length = ((data.length() / 16) + 1)*16 - data.length();
	for(int i = 0; i < pad_length; i++){
		data += '\4';
	}

	unsigned char ciphertext[data.length()];

	char iv[16];
	gnutls_rnd(GNUTLS_RND_NONCE, iv, 16);

	gnutls_cipher_set_iv(cipher_handle, iv, 16);

	gnutls_cipher_encrypt2(cipher_handle, data.c_str(), data.length(), ciphertext, data.length());

	string result = "";
	for(int i = 0; i < 16; i++){
		result += iv[i];
	}
	for(int i = 0; i < data.length(); i++){
		result += ciphertext[i];
	}

	return result;
}
