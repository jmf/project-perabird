#ifndef __FORMS_H__
#define __FORMS_H__

#include "Gui.h"

namespace Forms {
	class LoginForm : public Gui::Form {
		public:
			LoginForm(bool *_done);
		private:
			bool *done;
			Gui::Label label;
			Gui::Entry userEntry;
			Gui::PassEntry passEntry;
			Gui::Button cancelButton;
			Gui::Button acceptButton;
	};
}

#endif //__FORMS_H__
