#ifndef __GUIMAINMENU_H__
#define __GUIMAINMENU_H__

#include <irrlicht/irrlicht.h>
#include "Gui.h"

class GuiMainMenu
{
public:
	GuiMainMenu();
	~GuiMainMenu();
	static void show(bool menu);
	static void credits();
};

#endif //__GUIMAINMENU_H__
