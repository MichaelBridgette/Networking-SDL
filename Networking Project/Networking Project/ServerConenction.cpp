#include "ServerConnection.h"

ServerConnection::ServerConnection() 
{
}

ServerConnection::~ServerConnection() 
{
}

bool ServerConnection::initialise()
{
	std::string serverIp = "192.168.0.178";
	int serverPort = 54000;

	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cout << "Can't start Winsock, Err #" << wsResult << std::endl;
		return false;
	}

	// Create socket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return false;
	}

	// Make non-locking socket
	u_long type = 1;
	int result = ioctlsocket(m_socket, FIONBIO, &type);
	if (result != NO_ERROR) {
		std::cout << "Failed to create non-locking socket, Error: " << result << std::endl;
		return false;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(serverPort);
	inet_pton(AF_INET, serverIp.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(m_socket, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		// This causes errors
		//std::cout << "Can't connect to server, Error: " << WSAGetLastError() << std::endl;
		//closesocket(sock);
		//WSACleanup();
		//return;
	}
	return true;
}

void ServerConnection::sendMessage(std::string message)
{
	send(m_socket, message.c_str(), message.size() + 1, 0);
}

std::string ServerConnection::receiveMessage()
{
	ZeroMemory(m_buf, 4096);
	int bytesReceived = recv(m_socket, m_buf, 4096, 0);
	if (bytesReceived > 0)
	{
		std::string receivedMessage = std::string(m_buf, 0, bytesReceived);
		std::cout << "Received: " << receivedMessage << std::endl;
		return receivedMessage;
	}
	return "";
}

void ServerConnection::end()
{
	closesocket(m_socket);
	WSACleanup();
}