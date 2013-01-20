#include "Gui.h"
#include "GuiMainMenu.h"
#include "Video.h"
#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace gui;
using namespace core;

GuiMainMenu::GuiMainMenu()
{
}
	
GuiMainMenu::~GuiMainMenu()
{
}	


void GuiMainMenu::show()
{
	//Drawing the main menu:
	*Gui::guienv->addImage(Video::driver->getTexture("../media/logo.png"), position2d<int>(0,0));
	*Gui::guienv->addButton(rect<s32>(110,300,510,350), 0, 101,L"Play", L"Start the game");//101 is the ID
	*Gui::guienv->addButton(rect<s32>(110,380,510,430), 0, 102,L"Options", L"Change options");//102 is the ID
	*Gui::guienv->addButton(rect<s32>(110,460,510,510), 0, 103,L"Credits", L"Show Credits");//103 is the ID
	*Gui::guienv->addButton(rect<s32>(110,540,510,590), 0, 104,L"Quit", L"Exit Game");//104 is the ID
}

void GuiMainMenu::credits()
{
	*Gui::guienv->addImage(Video::driver->getTexture("../media/logo.png"), position2d<int>(500,500));
}
