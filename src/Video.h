#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <irrlicht/irrlicht.h>


using namespace irr;
using namespace video;
using namespace core;

class Video
{
public:
	Video();
	~Video();
	static void init(); 
	static IrrlichtDevice *device;
	static IVideoDriver *driver;
};

#endif //__VIDEO_H__
