#include "Gui.h"
#include "SimpleEventHandlers.h"

namespace SimpleEventHandlers {
	Toggle::Toggle(bool*_b) : b(_b) {}
	void Toggle::operator()(Gui::Event &e)
	{
		if (e.type == Gui::MOUSEUP)
			*b = !(*b);
	}
}
