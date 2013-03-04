#include <irrlicht/irrlicht.h>
#include <SDL/SDL_net.h>
#include "Gui.h"
#include "GuiMainMenu.h"
#include "Video.h"
#include "Event.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace gui;
using namespace video;

int main (int argc, char** argv)
{
	int width=640;//Width of the window
	int height=480;//Height of the window

	Video d;
	MyEventReceiver ev;
	ev.init();
	ISceneManager* smgr = Video::device->getSceneManager();//Get Scene manager enviroment
	Gui::env();//Get GUI enviroment
	
	while(d.device->run())
	{
		Gui::show();//Show the gui
		d.driver->beginScene(true, true, SColor(0,0,0,0));//Draw the backgorund color and begin the scene

		smgr->drawAll();//Let the scene manager do his job
		Gui::guienv->drawAll();//Draw the GUI

		d.driver->endScene();//End the scene
	}
	
	d.device->drop();//Stop the device
	return 0;//Everything okay!
}

