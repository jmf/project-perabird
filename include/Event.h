#ifndef __EVENT_H__
#define __EVENT_H__

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace gui;

class MyEventReceiver : public IEventReceiver
{
public:
	MyEventReceiver();
	~MyEventReceiver();
	virtual bool OnEvent(const SEvent& event);
	static void init();
private:
	static MyEventReceiver receiver;
};

#endif //__EVENT_H__
