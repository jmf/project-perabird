#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <string>

namespace Debug
{
	enum Level {
		DEBUG,
		WARNING,
		FATAL,
	};
	void print(Level level, std::string text);
}

#endif //__DEBUG_H__
