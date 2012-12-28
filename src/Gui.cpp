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
	guienv->addImage(Video::driver->getTexture("../media/logo.png"), position2d<int>(0,0));
	guienv->addEditBox(L"Useless Test Textbox", rect<s32>(350, 400, 550, 420));
	guienv->addEditBox(L"Even more Useless", rect<s32>(350, 440, 550, 460));
}


