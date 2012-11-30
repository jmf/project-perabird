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

#include <GL/gl.h>
#include <GL/glu.h>

void make2d(bool rel)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (rel)
		gluOrtho2D(0,1,0,1);
	else
	{
		int viewport[4];
		glGetIntegerv(GL_VIEWPORT,viewport);
		gluOrtho2D(0,viewport[2],viewport[3],0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

