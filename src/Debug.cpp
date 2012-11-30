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

#include <iostream>
#include <string>
#include "Debug.h"

namespace Debug
{
	void print(Level level, std::string text)
	{
		switch (level)
		{
			case DEBUG:
				std::cout << "[debug] " << text << std::endl;
				break;
			case WARNING:
				std::cout << "[WARNING] " << text << std::endl;
				break;
			case FATAL:
				std::cout << "[FATAL] " << text << std::endl;
				break;
			default:
				std::cout << text << std::endl;
				break;
		}
	}
}

