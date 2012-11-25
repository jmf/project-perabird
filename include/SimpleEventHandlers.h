#ifndef __SIMPLEEVENTHANDLERS_H__
#define __SIMPLEEVENTHANDLERS_H__

#include "Gui.h"

namespace SimpleEventHandlers {
	struct Toggle : Gui::EventHandler {
		Toggle(bool*_b);
		virtual void operator()(Gui::Event &e);
		private:
			bool *b;
	};
}

#endif //__SIMPLEEVENTHANDLERS_H__
