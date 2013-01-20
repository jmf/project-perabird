#ifndef __GUI_H__
#define __GUI_H__

#include <irrlicht/irrlicht.h>

class Gui
{
public:
	Gui();
	~Gui();
	static void env();
	static void show();
	static irr::gui::IGUIEnvironment* guienv;
};

#endif //__GUI_H__
