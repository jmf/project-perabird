/*
    Copyright (C) 2012 Zeg9
    
    This file is part of Project Perabird.
    Project Perabird is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Project Perabird is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Project Perabird.  If not, see <http://www.gnu.org/licenses/>
*/

#include <string>
#include <iostream>
#include <openssl/sha.h>
#include <SDL/SDL_net.h>
#include "Connection.h"
Connection::Connection(std::string host, int port)
{
	std::cout << "Connecting to " << host << ':' << port << "..." << std::endl;
	SDLNet_ResolveHost(&ip,host.c_str(),port);
	socket = SDLNet_TCP_Open(&ip);
}
Connection::~Connection()
{
	SDLNet_TCP_Close(socket);
	std::cout << "Connection closed" << std::endl;
}

bool Connection::isGood() { return socket; }

void Connection::send(void*msg, int size) {
	if (isGood())
		SDLNet_TCP_Send(socket,msg,size);
}
void Connection::sendByte(uint8_t i) {
	send(&i,sizeof(uint8_t));
}


void Connection::login(std::string user, std::string pswd)
{
	sendByte(MSG_BEGIN);
	sendByte(MSG_LOGIN);
	send((void*)user.c_str(),user.size());
	sendByte(MSG_SEP);
	unsigned char* hash = SHA256((const unsigned char*)pswd.c_str(),pswd.size(),0);
	send(hash, SHA256_DIGEST_LENGTH);
	sendByte(MSG_END);
}

