#include "Video.h"
#include "Gui.h"
#include "Event.h"
#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace gui;

MyEventReceiver MyEventReceiver::receiver;

MyEventReceiver::MyEventReceiver()
{
}

MyEventReceiver::~MyEventReceiver()
{
}

void MyEventReceiver::init()
{
	Video::device->setEventReceiver(&receiver);
}

bool MyEventReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();
		Gui::env();
		switch(event.GUIEvent.EventType)
		{
			case EGET_BUTTON_CLICKED:
			if (id == 101)
			{
				Video::device->closeDevice();
				return true;
			}
			break;
		}
	}
	return false;
}

