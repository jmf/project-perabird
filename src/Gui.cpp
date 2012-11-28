/*
    Copyright (C) 2012 Zeg9
    
    This file is part of Project Perabird.
    Project Perabird is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Project Perabird is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Project Perabird.  If not, see <http://www.gnu.org/licenses/>
*/

#include <map>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "Resources.h"
#include "Gui.h"

namespace Gui
{
	std::string stateToString(State state)
	{
		switch (state)
		{
			case INACTIVE:	return "inactive"; break;
			case NORMAL:	return "normal"; break;
			case OVER:	return "over"; break;
			case PRESS:	return "press"; break;
			default: break;
		} return "none";
	}
	std::string eventTypeToString(EventType eventType)
	{
		switch (eventType)
		{
			case MOUSEOVER:	return "mouseover"; break;
			case MOUSEOUT:	return "mouseout"; break;
			case MOUSEDOWN:	return "mousedown"; break;
			case MOUSEUP:	return "mouseup"; break;
			case KEYDOWN:	return "keydown"; break;
			case KEYUP:	return "keyup"; break;
			default: break;
		} return "none";
	}
	
	Font::Font(std::string name)
	{
		Resources *res = Resources::getInstance();
		texture = res->getTexture("gui/"+name+"/font");
	}
	
	void Font::render(char c)
	{
		float s = 1.0/16.0;
		float x = (c%16)*s;
		float y = -(c/16)*s;
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2d(x,y); glVertex2d(0,0);
				glTexCoord2d(x+s,y); glVertex2d(1,0);
				glTexCoord2d(x+s,y-s); glVertex2d(1,1);
				glTexCoord2d(x,y-s); glVertex2d(0,1);
			glEnd();
		glPopMatrix();
	}
	
	void Font::render(std::string text)
	{
		glPushMatrix();
			for (int i = 0; i < text.size(); i++)
			{
				render(text[i]);
				glTranslated(.5,0,0);
			}
		glPopMatrix();
	}
	
	
	Theme::Theme(std::string name) : font(name)
	{
		Resources *res = Resources::getInstance();
		for (int i = FIRST_STATE+1; i < LAST_STATE; i++)
			textures[State(i)] = res->getTexture(
				"gui/"+name+'/'+stateToString(State(i)));
		for (int i = FIRST_EVENTTYPE+1; i < LAST_EVENTTYPE; i++)
			sounds[EventType(i)] = res->getSound(
				"gui/"+name+'/'+eventTypeToString(EventType(i)));
	}
	GLuint Theme::getTexture(State state) { return textures[state]; }
	Mix_Chunk* Theme::getSound(EventType eventType) { return sounds[eventType]; }
	Font*Theme::getFont() { return &font; }
	
	Event::Event(): type(NONE), key(0), x(-1), y(-1), button(-1) {}
	
	Element::Element (Theme*_theme, std::string _text, int _x, int _y, int _w, int _h):
		theme(_theme),
		text(_text),
		xrel(_x), yrel(_y),
		w(_w), h(_h),
		hAlign(HALIGN_LEFT), vAlign(VALIGN_TOP),
		state(NORMAL),
		textAlign(TEXTALIGN_CENTER)
	{
		calculatePosition();
	}
	Element::~Element()
	{
		for (int i = 0; i < eventHandlers.size(); i++)
			delete eventHandlers[i];
	}
	void Element::addEventHandler(EventHandler *e)
	{
		eventHandlers.push_back(e);
	}
	void Element::render()
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glTranslated(x,y,0);
			if (theme->getTexture(getState()))
			{
				glBindTexture(GL_TEXTURE_2D, theme->getTexture(getState()));
				glColor3ub(255,255,255);
				glPushMatrix();
					glScaled(h,h,1);
					glBegin(GL_QUADS);
						glTexCoord2d(0,0); glVertex2d(0,0);
						glTexCoord2d(1,0); glVertex2d(1,0);
						glTexCoord2d(1,-1); glVertex2d(1,1);
						glTexCoord2d(0,-1); glVertex2d(0,1);
					glEnd();
				glPopMatrix();
				glTranslated(h,0,0);
				glPushMatrix();
					glScaled(w-2*h,h,1);
					glBegin(GL_QUADS);
						glTexCoord2d(.8,0); glVertex2d(0,0);
						glTexCoord2d(.8,0); glVertex2d(1,0);
						glTexCoord2d(.8,-1); glVertex2d(1,1);
						glTexCoord2d(.8,-1); glVertex2d(0,1);
					glEnd();
				glPopMatrix();
				glTranslated(w-2*h,0,0);
				glPushMatrix();
					glScaled(h,h,1);
					glBegin(GL_QUADS);
						glTexCoord2d(1,0); glVertex2d(0,0);
						glTexCoord2d(0,0); glVertex2d(1,0);
						glTexCoord2d(0,-1); glVertex2d(1,1);
						glTexCoord2d(1,-1); glVertex2d(0,1);
					glEnd();
				glPopMatrix();
			}
			glLoadIdentity();
			glTranslated(x,y,0);
			switch (textAlign)
			{
				case TEXTALIGN_LEFT:
					glTranslated(h/2,h/2,0);
					glScalef(16,16,1);
					glTranslated(-.5,-.5,0);
					break;
				case TEXTALIGN_CENTER:
					glTranslated(w/2,h/2,0);
					glScalef(16,16,1);
					glTranslated(-.25*text.size()-.25,-.5,0);
					break;
				case TEXTALIGN_RIGHT:
					glTranslated(w-h/2,h/2,0);
					glScalef(16,16,1);
					glTranslated(-.5*text.size(),-.5,0);
					break;
				default:
					break;
			}
			theme->getFont()->render(getText());
		glPopMatrix();
	}
	void Element::event(Event &e)
	{
		Mix_PlayChannel(-1,theme->getSound(e.type),0);
		if (e.type == RESIZE)
			calculatePosition();
		elEvent(e);
		for (int i = 0; i < eventHandlers.size(); i++)
			(*eventHandlers[i]) (e);
	}
	bool Element::sdlEvent(SDL_Event &e)
	{
		Event ne;
		if (getState() != INACTIVE) switch (e.type)
		{
			case SDL_MOUSEMOTION:
				if (	e.motion.x >= x &&
					e.motion.x <= x+w &&
					e.motion.y >= y &&
					e.motion.y <= y+h)
				{ if(getState() == NORMAL) ne.type = MOUSEOVER; }
				else if (getState() != NORMAL)
					ne.type = MOUSEOUT;
				ne.x = e.motion.x;
				ne.y = e.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					if (	e.button.x >= x &&
						e.button.x <= x+w &&
						e.button.y >= y &&
						e.button.y <= y+h) ne.type = MOUSEDOWN;
					else if (getState()==PRESS) ne.type = MOUSEDOWNOUT;
					ne.x = e.button.x;
					ne.y = e.button.y;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (getState() == PRESS) ne.type = MOUSEUP;
				ne.x = e.button.x;
				ne.y = e.button.y;
				break;
			case SDL_KEYDOWN:
				if (getState() == PRESS)
				{
					if (e.key.keysym.unicode == '\r')
					{
						ne.type = MOUSEDOWN;
						event(ne);
						ne.type = MOUSEUP;
						event(ne);
						ne.type = MOUSEOUT;
						event(ne);
					}
					ne.type = KEYDOWN;
					ne.key = e.key.keysym.unicode;
				}
				break;
			case SDL_KEYUP:
				if (getState() == PRESS)
				{
					ne.type = KEYUP;
					ne.key = e.key.keysym.unicode;
				}
				break;
			default:
				break;
		}
		switch (e.type)
		{
			case SDL_VIDEORESIZE:
				ne.type = RESIZE;
				ne.x = e.resize.w;
				ne.y = e.resize.h;
				break;
			default:
				break;
		}
		if (ne.type == NONE) return false;
		event(ne);
		return true;
	}
	
	void Element::setPosition(int _x, int _y) { xrel=_x; yrel=_y; calculatePosition(); }
	void Element::setSize(int _w, int _h) { w=_w; h=_h; calculatePosition(); }
	void Element::setAlignment(HAlign _hAlign, VAlign _vAlign) { hAlign=_hAlign; vAlign=_vAlign; calculatePosition(); }
	void Element::setTextAlign(TextAlign _textAlign) { textAlign=_textAlign; }
	void Element::calculatePosition()
	{
		GLint viewport [4];
		glGetIntegerv(GL_VIEWPORT,viewport);
		int sw = viewport[2] - viewport[0];
		int sh = viewport[3] - viewport[1];
		switch (hAlign) {
			case HALIGN_LEFT:
				x=xrel;
				break;
			case HALIGN_RIGHT:
				x=sw-getWidth()-xrel;
				break;
			case HALIGN_MIDDLE:
				x=sw/2-getWidth()/2+xrel;
				break;
			default:
				x=xrel;
				break;
		}
		switch (vAlign) {
			case VALIGN_TOP:
				y=yrel;
				break;
			case VALIGN_BOTTOM:
				y=sh-getHeight()-yrel;
				break;
			case VALIGN_MIDDLE:
				y=sh/2-getHeight()/2+yrel;
				break;
			default:
				y=yrel;
				break;
		}
	}
	int Element::getX() { return x; }
	int Element::getY() { return y; }
	int Element::getWidth() { return w; }
	int Element::getHeight() { return h; }
	void Element::setText(std::string _text) { text = _text; }
	std::string Element::getText() { return text; }
	void Element::setState(State _state) { state = _state; }
	State Element::getState() { return state; }
	
	Label::Label(Theme*_theme, std::string _text, int _x, int _y, int _w, int _h)
	: Element(_theme, _text, _x, _y, _w, _h) {}
	State Label::getState() { return INACTIVE; }
	void Label::elEvent(Event &e) {}
	
	Button::Button(Theme*_theme, std::string _text, int _x, int _y, int _w, int _h)
	: Element(_theme, _text, _x, _y, _w, _h) {}
	
	void Button::elEvent(Event &e)
	{
		if (getState()!=INACTIVE) switch (e.type)
		{
			case MOUSEOVER:
				setState(OVER);
				break;
			case MOUSEOUT:
				setState(NORMAL);
				break;
			case MOUSEDOWN:
				setState(PRESS);
				break;
			case MOUSEUP:
				setState(OVER);
				break;
			case KEYDOWN: if (e.key == ' ')
			{
				Gui::Event ne;
				ne.type = MOUSEDOWN;
				event(ne);
				ne.type = MOUSEUP;
				event(ne);
				ne.type = MOUSEOUT;
				event(ne);
			}
		}
	}
	
	Entry::Entry(Theme*_theme, std::string _text, int _x, int _y, int _w, int _h)
	: Element(_theme, _text, _x, _y, _w, _h)
	{
		setTextAlign(TEXTALIGN_LEFT);
	}
	
	std::string Entry::getEntryText() { return text; }
	
	std::string Entry::getText()
	{
		if (getState()==PRESS && SDL_GetTicks()%1000>250)
			return Element::getText() + '|';
		else
			return Element::getText();
	}
	
	void Entry::elEvent(Event &e)
	{
		if (getState()!=INACTIVE) switch (e.type)
		{
			case MOUSEOVER:
				setState(OVER);
				break;
			case MOUSEOUT:
				if (getState() == OVER) setState(NORMAL);
				break;
			case MOUSEDOWN:
				setState(PRESS);
				break;
			case MOUSEDOWNOUT:
				setState(NORMAL);
				break;
			case KEYDOWN:
				if (getState()==PRESS)
				{
					if (e.key >= ' '  && e.key <= '~')
						text+=e.key;
					else if (e.key == 8 || e.key == 127)
						text = text.substr(0,text.size()-1);
					/*else
						std::cout << int(e.key) << std::endl;*/
				}
				break;
		}
	}
	
	PassEntry::PassEntry(Theme*_theme, std::string _text, int _x, int _y, int _w, int _h)
	 : Entry(_theme,_text,_x,_y,_w,_h) {}
	
	std::string PassEntry::getText()
	{
		std::string mytext = "";
		for (int i = 0; i < Element::getText().size(); i++)
			mytext += '*';
		if (getState()==PRESS && SDL_GetTicks()%1000>250)
			return mytext + '|';
		else
			return mytext;
	}

	Form::Form() : elements() {}
	Form::~Form() {}
	void Form::add(Element*e) { elements.push_back(e); }
	void Form::render()
	{
		for (int i = 0; i < elements.size(); i++)
			elements[i]->render();
	}
	bool Form::sdlEvent(SDL_Event &e)
	{
		bool r(false);
		bool hasTabbed(false);
		for (int i = 0; i < elements.size(); i++)
		{
			if(elements[i]->sdlEvent(e)) r = true;
			if (	!hasTabbed
				&& e.type == SDL_KEYDOWN
				&& elements[i]->getState()==PRESS
				&& e.key.keysym.sym == SDLK_TAB)
			{
				int j = i;
				do
				{
					if(e.key.keysym.mod & KMOD_SHIFT) j = j-1; else j = j+1;
					if (j < 0)
						j=elements.size()-1;
					else if (j>=elements.size())
						j=0;
				} while (elements[j]->getState()==INACTIVE);
				elements[i]->setState(NORMAL);
				Event ne;
				ne.type = MOUSEOVER;
				elements[j]->event(ne);
				elements[j]->setState(PRESS);
				hasTabbed = true;
			}
		}
		if (!hasTabbed && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB)
		{
			int j = 0;
			while (elements[j]->getState()==INACTIVE)
			{
				if(e.key.keysym.mod & KMOD_SHIFT) j = j-1; else j = j+1;
				if (j < 0)
					j=elements.size()-1;
				else if (j>=elements.size())
					j=0;
			}
			Event ne;
			ne.type = MOUSEOVER;
			elements[j]->event(ne);
			elements[j]->setState(PRESS);
			hasTabbed = true;
		}
		return r;
	}
	Element* Form::getElement(int id) { return elements[id]; }
	int Form::getCount() { return elements.size(); }
}

