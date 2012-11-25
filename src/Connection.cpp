#include <string>
#include <iostream>
#include <openssl/sha.h>
#include <SDL/SDL_net.h>
#include "Connection.h"
Connection::Connection(std::string host, int port)
{
	std::cout << "Connecting to " << host << ':' << port << "..." << std::endl;
	SDLNet_ResolveHost(&ip,host.c_str(),port);
	socket = SDLNet_TCP_Open(&ip);
}
Connection::~Connection()
{
	SDLNet_TCP_Close(socket);
	std::cout << "Connection closed" << std::endl;
}

bool Connection::isGood() { return socket; }

void Connection::send(void*msg, int size) {
	if (isGood())
		SDLNet_TCP_Send(socket,msg,size);
}
void Connection::sendByte(uint8_t i) {
	send(&i,sizeof(uint8_t));
}


void Connection::login(std::string user, std::string pswd)
{
	sendByte(MSG_BEGIN);
	sendByte(MSG_LOGIN);
	send((void*)user.c_str(),user.size());
	sendByte(MSG_SEP);
	unsigned char* hash = SHA256((const unsigned char*)pswd.c_str(),pswd.size(),0);
	send(hash, SHA256_DIGEST_LENGTH);
	sendByte(MSG_END);
}

