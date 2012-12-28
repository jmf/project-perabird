#include "Video.h"
#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace video;
using namespace core;

IrrlichtDevice *Video::device(0);
IVideoDriver *Video::driver(0);


Video::Video()
{
}
	
Video::~Video()
{
}	

void Video::init()
{
	Video::device = createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16, false, false, false, 0);
	//Initializing IrrlichtDevice|| Width and height must be added later
	Video::device->setWindowCaption(L"Project Perabird");//Set window caption

	Video::driver = Video::device->getVideoDriver();//Get Video driver

}


