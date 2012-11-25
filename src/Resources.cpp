
#include "Resources.h"
#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Debug.h"

Resources Resources::instance;
Resources::Resources() {}
Resources::~Resources()
{
	for (std::map<std::string,Mix_Chunk*>::iterator i=sounds.begin();i!=sounds.end();i++)
		unloadSound(i->first);
}
Resources* Resources::getInstance()
{
	return &instance;
}

void Resources::loadTexture(std::string name)
{
	SDL_Surface* orig = IMG_Load((DIR_IMAGES+name+".png").c_str());
	if (!orig)
	{
		Debug::print(Debug::WARNING, "Can't load texture: "+name);
		return;
	}
	// Vertically flip the surface
	int current_line,pitch;
	SDL_Surface * surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
		orig->w,orig->h,
		orig->format->BitsPerPixel,
		orig->format->Rmask,
		orig->format->Gmask,
		orig->format->Bmask,
		orig->format->Amask);

	SDL_LockSurface(orig);
	SDL_LockSurface(surface);

	pitch = orig->pitch;
	for (current_line = 0; current_line < orig->h; current_line ++)
	{
		memcpy(&((unsigned char* )surface->pixels)[current_line*pitch],
			&((unsigned char* )orig->pixels)[(orig->h - 1  -
			current_line)*pitch],
			pitch);
	}

	SDL_UnlockSurface(surface);
	SDL_UnlockSurface(orig);
	SDL_FreeSurface(orig);
	// Load it into a gl texture
	GLuint texture;
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	SDL_PixelFormat *format = surface->format;
	
	if (format->Amask)
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
			surface->w, surface->h, GL_RGBA,GL_UNSIGNED_BYTE, surface->pixels);
	}
	else
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
			surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	}
	SDL_FreeSurface(surface);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	textures[name] = texture;
	Debug::print(Debug::DEBUG, "Loaded texture: "+name);
}

GLuint Resources::getTexture(std::string name)
{
	if (textures.find(name) == textures.end())
		loadTexture(name);
	if (textures.find(name) == textures.end()) return 0;
	return textures[name];
}

void Resources::unloadSound(std::string name)
{
	if (sounds.find(name) != sounds.end())
	{
		Mix_FreeChunk(sounds[name]);
		Debug::print(Debug::DEBUG, "Unloaded sound: "+name);
	}
}

void Resources::loadSound(std::string name)
{
	unloadSound(name);
	Mix_Chunk* sound = Mix_LoadWAV((DIR_SOUNDS+name+".ogg").c_str());
	if (sound)
	{
		sounds[name] = sound;
		Debug::print(Debug::DEBUG, "Loaded sound: "+name);
	} else Debug::print(Debug::WARNING,"Can't load sound: "+name);
}

Mix_Chunk *Resources::getSound(std::string name)
{
	if (sounds.find(name) == sounds.end())
		loadSound(name);
	if (sounds.find(name) == sounds.end()) return 0;
	return sounds[name];
}

void Resources::loadGuiTheme(std::string name)
{
	guiThemes[name] = new Gui::Theme (name);
}
Gui::Theme *Resources::getGuiTheme(std::string name)
{
	if (guiThemes.find(name) == guiThemes.end())
		loadGuiTheme(name);
	return guiThemes[name];
}

