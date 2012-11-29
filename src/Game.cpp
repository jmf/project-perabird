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
#include <GL/gl.h>
#include <GL/glu.h>
#include "Connection.h"
#include "Console.h"
#include "Game.h"


Game Game::instance;
Game::Game(): connection(0) {}
Game::~Game() {
	delete connection;
}
Game* Game::getInstance () {
	return &instance;
}


void Game::connect(std::string host, int port, std::string user, std::string pswd) {
	disconnect();
	connection = new Connection(host,port);
	if (!connection->isGood()) {
		getConsole()->print("[Can't connect to server]");
		disconnect();
	}
	else if (connection->login(user,pswd)) {
		username = user;
		getConsole()->print("[Login accepted]");
	}
	else
		getConsole()->print("[Bad login]");
}
void Game::disconnect() {
	if (!connection) return;
	delete connection;
	connection = 0;
}

void Game::sendMessage(std::string msg)
{
	connection->sendByte(MSG_BEGIN);
	connection->sendByte(MSG_CHAT);
	connection->send((void*)msg.c_str(),msg.size());
	connection->sendByte(MSG_END);
}

Console *Game::getConsole() {
	return &console;
}

void Game::render() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
	gluOrtho2D(0,viewport[2],viewport[3],0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	getConsole()->render();
}


