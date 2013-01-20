#include "Gui.h"
#include "GuiMainMenu.h"
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

void Gui::show()
{
	GuiMainMenu::show();
}
