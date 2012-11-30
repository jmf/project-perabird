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
#include <SDL/SDL.h>
#include "Debug.h"
#include "Connection.h"
#include "Console.h"
#include "Resources.h"
#include "Tools.h"
#include "Game.h"


Game *Game::instance(0);
Game::Game(): connection(0) { Debug::print(Debug::DEBUG,"test");}
Game::~Game() {
	delete connection;
}
Game* Game::getInstance () {
	return instance;
}
void Game::init() {
	instance = new Game;
}
void Game::quit() {
	delete instance; instance = 0;
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
	if (!connection) return;
	if (msg=="") return;
	connection->sendByte(MSG_BEGIN);
	connection->sendByte(MSG_CHAT);
	connection->send((void*)msg.c_str(),msg.size());
	connection->sendByte(MSG_END);
}

Console *Game::getConsole() {
	return &console;
}

void Game::toggleChat() { chatOpened = !chatOpened; }

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// background
	if (!(connection && connection->isGood()))
	{
		make2d(true);
		glBindTexture(GL_TEXTURE_2D,RESOURCES->getTexture("login"));
		glBegin(GL_QUADS);
			glTexCoord2d(0,0); glVertex2d(0,0);
			glTexCoord2d(1,0); glVertex2d(1,0);
			glTexCoord2d(1,1); glVertex2d(1,1);
			glTexCoord2d(0,1); glVertex2d(0,1);
		glEnd();
	}
	// form rendering
	make2d(false);
	getConsole()->render();
	if (!(connection && connection->isGood()))
		loginForm.render();
	else if (chatOpened)
		chatForm.render();
}

void Game::event(SDL_Event &e) {
	bool guiEvent(false);
	if (!(connection && connection->isGood()))
		guiEvent = loginForm.sdlEvent(e);
	else
	{
		if (chatOpened)
		guiEvent = chatForm.sdlEvent(e);
		switch(e.type) {
			case SDL_KEYDOWN:
				switch(e.key.keysym.unicode) {
					case '\r':
						toggleChat();
					default:
						break;
				} break;
			default:
				break;
		}
	}
}

bool Game::alive() { return !done; }
void Game::exit() { done = true; }

