#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <map>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include "Gui.h"

#define DIR_DATA "./data/"
#define DIR_IMAGES DIR_DATA"images/"
#define DIR_SOUNDS DIR_DATA"sounds/"

#define RESOURCES Resources::getInstance()

class Resources
{
	public:
		static Resources *getInstance();
		
		void loadTexture(std::string name);
		GLuint getTexture(std::string name);
		void unloadSound(std::string name);
		void loadSound(std::string name);
		Mix_Chunk* getSound(std::string name);
		void loadGuiTheme(std::string name);
		Gui::Theme* getGuiTheme(std::string name);
	private:
		std::map<std::string,GLuint> textures;
		std::map<std::string,Mix_Chunk*> sounds;
		std::map<std::string,Gui::Theme*> guiThemes;
	private:
		Resources();
		~Resources();
		static Resources instance;
};

#endif //__RESOURCES_H__
