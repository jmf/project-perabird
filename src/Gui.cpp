#include "Gui.h"
#include "Video.h"
#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace gui;
using namespace core;

IGUIEnvironment *Gui::guienv(0);

Gui::Gui()
{
}
	
Gui::~Gui()
{
}	

void Gui::env()
{
	guienv = Video::device->getGUIEnvironment(); //Get GUI
}

void Gui::start()
{
	//Drawing the main menu:
	guienv->addStaticText(L"Coming soon",rect<s32>(50,50,260,22), true);
	guienv->addImage(Video::driver->getTexture("../media/logo.png"), position2d<int>(0,200));
}


