#include <iostream>
#include <vector>
#include <sstream>
#include <irrlicht/irrlicht.h>
#include <SDL/SDL_net.h>
#include "Gui.h"
#include "Video.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace gui;
using namespace video;

int main (int argc, char**argv)
{
	int width=640;//Width of the window
	int height=480;//Height of the window

	SDLNet_Init();//Initializing SDLNet
	
	Video::init();//Initialize the Video driver
	ISceneManager* smgr = Video::device->getSceneManager();//Get Scene manager enviroment
	Gui::env();//Get GUI enviroment
	Gui::start();//Show the gui
	while(Video::device->run())
	{
		Video::driver->beginScene(true, true, SColor(255,100,101,140));

		smgr->drawAll();
		Gui::guienv->drawAll();

		Video::driver->endScene();
	}
	
	Video::device->drop();
	SDLNet_Quit();//Quit SDLNet
	return 0;
}

