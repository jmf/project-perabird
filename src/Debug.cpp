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
				//std::cout << "[debug] " << text << std::endl;
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

