#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>
#include <GL/gl.h>
#include <GL/glu.h>
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
	
	Resources *res = Resources::getInstance();
	
	Mix_Chunk*sound_jump = res->getSound("jump");
	bool done(false);
	SDL_Event e;
	int mx,my;
	int x(0),y(0); float z(0);
	int points[800];
	srand(time(0));
	
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
			if (!form.sdlEvent(e)) switch(e.type)
			{
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
						case SDLK_SPACE:
							Mix_PlayChannel(-1,sound_jump,0);
							break;
						default:
							break;
					}
					break;
				default:
					break;
			} if (done) break;
		}
		int x,y;
		if (done) break;
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,1,0,1);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			glColor3d(1,1,1);
			glVertex2d(0,0);
			glVertex2d(1,0);
			glColor3d(.75,.75,1);
			glVertex2d(1,1);
			glVertex2d(0,1);
		glEnd();
		glMatrixMode(GL_MODELVIEW);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,width,height,0);
		glMatrixMode(GL_MODELVIEW);
		form.render();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,1,0,1);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINES);
			glColor3d(0,0,0);
			glVertex2d(.5,0);
			glVertex2d(.5,1);
			glVertex2d(0,.5);
			glVertex2d(1,.5);
		glEnd();
		glFlush();
		SDL_GL_SwapBuffers();
	}
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	Mix_CloseAudio();
	SDLNet_Quit();
	SDL_Quit();
	Debug::print(Debug::DEBUG,"Exiting...");
}

