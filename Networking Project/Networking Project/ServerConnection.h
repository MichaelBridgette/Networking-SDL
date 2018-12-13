#ifndef SERVERCONNECTION_H
#define SERVERCONENCTION_H

#include <iostream>
#include <string>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class ServerConnection
{
public:
	ServerConnection();
	~ServerConnection();
	bool initialise();
	void sendMessage(std::string message);
	std::string receiveMessage();
	void end();
private:
	SOCKET m_socket;
	char m_buf[4096];
};

#endif // !SERVERCONENCTION_H