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

#include <vector>
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include "Gui.h"
#include "Resources.h"
#include "Console.h"

Console::Console() : font(0) {}
Console::~Console() {
	if (font)
		delete font;
}

void Console::init()
{
	font = new Gui::Font("console");
}

void Console::print(std::string line)
{
	text.push_back(line);
}

void Console::event(SDL_Event &e)
{
	
}

void Console::render()
{
	if(!font) return;
	glPushMatrix();
	glScalef(16,16,1);
	int startline = text.size()-10;
	if (text.size() < 10) startline = 0;
	int endline = text.size();
	for (unsigned int i = startline; i < endline; i++)
	{
		font->render(text[i]);
		glTranslated(0,1,0);
	}
	glPopMatrix();
}

