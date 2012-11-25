#ifndef __CONNECTION_H__
#define __CONNECTION_H__
#include <string>
#include <SDL/SDL_net.h>

#define MSG_SEP 0
#define MSG_BEGIN 1
#define MSG_END 2
#define MSG_LOGIN 5

class Connection
{
	public:
		Connection(std::string host, int port);
		~Connection();
		bool isGood();
		void send(void*msg, int size);
		void sendByte(uint8_t i);
		void login(std::string user, std::string pswd); // pswd will be hashed
	private:
		IPaddress ip;
		TCPsocket socket;
};

#endif //__CONNECTION_H__
