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

#include <iostream>
#include <vector>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Game.h"
#include "Gui.h"
#include "Forms.h"
#include "Resources.h"
#include "Connection.h"
#include "Debug.h"


int main (int argc, char**argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDLNet_Init();
	SDL_WM_SetCaption("test",0);
	SDL_EnableUNICODE(SDL_ENABLE);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	glClearColor(0,0,0,0);
	int width(800), height(600);
	SDL_SetVideoMode(width,height,32,SDL_OPENGL|SDL_RESIZABLE);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	Mix_AllocateChannels(8);
	Game::getInstance()->getConsole()->init();
	
	Resources *res = Resources::getInstance();
	
	bool done(false);
	int oldtime(SDL_GetTicks()), newtime(oldtime);
	SDL_Event e;
	
	Forms::LoginForm form(&done);
	
	bool inZone = false;
	
	while (!done)
	{
		while (SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_VIDEORESIZE:
					width =e.resize.w;
					height= e.resize.h;
					SDL_SetVideoMode(width,height, 32, SDL_OPENGL | SDL_RESIZABLE);
					glViewport(0,0,width,height);
					break;
				case SDL_QUIT:
					done = true;
					break;
			} if (done) break;
			form.sdlEvent(e);
			if (done) break;
		}
		int x,y;
		if (done) break;
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,width,height,0);
		glMatrixMode(GL_MODELVIEW);
		form.render();
		Game::getInstance()->getConsole()->render();
		glFlush();
		SDL_GL_SwapBuffers();
		newtime = SDL_GetTicks();
		if (newtime-oldtime < 30) SDL_Delay(30-(newtime-oldtime));
		oldtime = newtime;
	}
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	Mix_CloseAudio();
	SDLNet_Quit();
	SDL_Quit();
	Debug::print(Debug::DEBUG,"Exiting...");
}

