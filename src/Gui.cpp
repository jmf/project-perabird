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
	guienv->addButton(rect<s32>(210,300,610,350), 0, 101,L"Play", L"Start the game");//101 is the ID
	guienv->addButton(rect<s32>(210,380,610,430), 0, 102,L"Options", L"Change options");//102 is the ID
	guienv->addButton(rect<s32>(210,460,610,510), 0, 103,L"Credits", L"Show Credits");//103 is the ID
	guienv->addButton(rect<s32>(210,540,610,590), 0, 104,L"Quit", L"Exit Game");//104 is the ID
}


