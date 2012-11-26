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

#ifndef __CONNECTION_H__
#define __CONNECTION_H__
#include <string>
#include <SDL/SDL_net.h>

#define MSG_SEP 0
#define MSG_BEGIN 1
#define MSG_END 2
#define MSG_LOGIN 5
#define MSG_JOIN 6
#define MSG_QUIT 7
#define MSG_PLAYERPOS 8

class Connection
{
	public:
		Connection(std::string host, int port);
		~Connection();
		bool isGood();
		void send(void*msg, int size);
		void sendByte(uint8_t i);
		uint8_t * recv(uint8_t buffer[], int size);
		uint8_t recvByte();
		void login(std::string user, std::string pswd); // pswd will be hashed
	private:
		IPaddress ip;
		TCPsocket socket;
};

#endif //__CONNECTION_H__
