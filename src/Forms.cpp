#include "Gui.h"
#include "Resources.h"
#include "SimpleEventHandlers.h"
#include "Connection.h"
#include "Forms.h"

namespace Forms {
	struct ConnectEventHandler : Gui::EventHandler
	{
		ConnectEventHandler(Gui::Entry* _userEntry, Gui::PassEntry *_passEntry)
		 : userEntry(_userEntry), passEntry(_passEntry) {}
		virtual void operator()(Gui::Event &e)
		{
			if (e.type == Gui::MOUSEUP)
			{
				if (userEntry->getEntryText() == "" || passEntry->getEntryText() == "") return;
				Connection c("localhost",5153);
				c.login(userEntry->getEntryText(),passEntry->getEntryText());
			}
		}
		private:
			Gui::Entry * userEntry;
			Gui::PassEntry * passEntry;
	};
	LoginForm::LoginForm(bool *_done) :
		done(_done),
		label(RESOURCES->getGuiTheme("button"),"Login"),
		userEntry(RESOURCES->getGuiTheme("entry")),
		passEntry(RESOURCES->getGuiTheme("entry")),
		cancelButton(RESOURCES->getGuiTheme("button"),"Cancel"),
		acceptButton(RESOURCES->getGuiTheme("button"),"Accept")
	{
		using namespace Gui;
		label.setPosition(0,-16-2-32-4);
		label.setSize(128,32);
		label.setAlignment(HALIGN_MIDDLE,VALIGN_MIDDLE);
		add(&label);
		userEntry.setPosition(0,-16-2);
		userEntry.setSize(128,32);
		userEntry.setAlignment(HALIGN_MIDDLE,VALIGN_MIDDLE);
		add(&userEntry);
		passEntry.setPosition(0,16+2);
		passEntry.setSize(128,32);
		passEntry.setAlignment(HALIGN_MIDDLE,VALIGN_MIDDLE);
		add(&passEntry);
		cancelButton.setPosition(-32,16+2+32+4);
		cancelButton.setSize(64,32);
		cancelButton.setAlignment(HALIGN_MIDDLE,VALIGN_MIDDLE);
		cancelButton.addEventHandler(new SimpleEventHandlers::Toggle(done));
		add(&cancelButton);
		acceptButton.setPosition(32,16+2+32+4);
		acceptButton.setSize(64,32);
		acceptButton.setAlignment(HALIGN_MIDDLE,VALIGN_MIDDLE);
		acceptButton.addEventHandler(new ConnectEventHandler(&userEntry,&passEntry));
		add(&acceptButton);
	}
}
