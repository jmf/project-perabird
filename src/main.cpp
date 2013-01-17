#include <irrlicht/irrlicht.h>
#include <SDL/SDL_net.h>
#include "Gui.h"
#include "Video.h"
#include "Event.h"
#include "Connection.h"

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
	MyEventReceiver::init();
	ISceneManager* smgr = Video::device->getSceneManager();//Get Scene manager enviroment
	Gui::env();//Get GUI enviroment
	Gui::start();//Show the gui

	while(Video::device->run())
	{
		Video::driver->beginScene(true, true, SColor(0,0,0,0));//Draw the backgorund color and begin the scene

		smgr->drawAll();//Let the scene manager do his job
		Gui::guienv->drawAll();//Draw the GUI

		Video::driver->endScene();//End the scene
	}
	
	Video::device->drop();//Stop the device
	SDLNet_Quit();//Quit SDLNet
	return 0;//Everything okay!
}

